/*
4.3. Планировщик процессов
В операционной системе Technux есть планировщик процессов.
Каждый процесс характеризуется:
- приоритетом P;
- временем, которое он уже отработал t;
- временем, которое необходимо для завершения работы процесса T.
Планировщик процессов выбирает процесс с минимальным значением P * (t + 1),
выполняет его время P и кладет обратно в очередь процессов. Если выполняется
условие t >= T, то процесс считается завершенным и удаляется из очереди.
Требуется посчитать кол-во переключений процессора.
*/

#include <cassert>
#include <iostream>

struct Process {
  Process() : P_(0), t_(0), T_(0) {}
  explicit Process(int P, int T);
  int P_, t_, T_;
};

Process::Process(int P, int T) {
  P_ = P;
  t_ = 0;
  T_ = T;
}

class ProcessComparator {
 public:
  bool operator()(const Process &first, const Process &second) {
    return first.P_ * (first.t_ + 1) < second.P_ * (second.t_ + 1);
  }
};

template <typename T>
class DefaultLessComparator {
 public:
  bool operator()(const T &first, const T &second) { return first < second; }
};

template <typename T, typename Comparator = DefaultLessComparator<T>>
class Heap {
 public:
  Heap()
      : bufferLength(2),
        elementsCount(0),
        buffer(new T[bufferLength]),
        cmp(Comparator()) {}
  explicit Heap(int size);
  ~Heap();

  T ExtractTop();
  void Add(const T &element);
  bool IsEmpty() { return elementsCount == 0; };

  void bufferExpansion();

 private:
  int bufferLength;
  int elementsCount;
  T *buffer;
  void siftDown(int index);
  void siftUp(int index);
  Comparator cmp;
};

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(int size) {
  cmp = Comparator();
  bufferLength = size;
  elementsCount = 0;
  buffer = new T[bufferLength];
}

template <typename T, typename Comparator>
Heap<T, Comparator>::~Heap() {
  while (!IsEmpty()) {
    ExtractTop();
  }
  delete[] buffer;
}

template <typename T, typename Comparator>
T Heap<T, Comparator>::ExtractTop() {
  assert(!IsEmpty());

  T result = buffer[0];

  elementsCount--;
  buffer[0] = buffer[elementsCount];

  if (!IsEmpty()) {
    siftDown(0);
  }

  return result;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::siftDown(int index) {
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  int least = index;

  if (left < elementsCount && cmp(buffer[left], buffer[index])) {
    least = left;
  }
  if (right < elementsCount && cmp(buffer[right], buffer[least])) least = right;

  if (least != index) {
    std::swap(buffer[index], buffer[least]);
    siftDown(least);
  }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::siftUp(int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;

    if (!cmp(buffer[index], buffer[parent])) return;

    std::swap(buffer[index], buffer[parent]);
    index = parent;
  }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::Add(const T &element) {
  if (elementsCount == bufferLength) {
    bufferExpansion();
  }

  buffer[elementsCount] = element;
  siftUp(elementsCount);
  elementsCount++;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::bufferExpansion() {
  int new_length = bufferLength * 1.5;

  T *new_buffer = new T[new_length];

  for (int i = 0; i < bufferLength; i++) {
    new_buffer[i] = buffer[i];
  }

  delete[] buffer;

  buffer = new_buffer;
  bufferLength = new_length;
}

int main(int argc, const char *argv[]) {
  int n = 0;
  std::cin >> n;

  Heap<Process, ProcessComparator> heap;

  int P = 0, T = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> P >> T;
    heap.Add(Process(P, T));
  }

  int switchCount = 0;
  while (!heap.IsEmpty()) {
    Process top = heap.ExtractTop();
    top.t_ += top.P_;
    if (top.t_ < top.T_) heap.Add(top);
    switchCount++;
  }

  std::cout << switchCount;

  return 0;
}