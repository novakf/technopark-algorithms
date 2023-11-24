/*
3.2. Реализовать дек с динамическим зацикленным буфером.
*/

#include <iostream>

class Deque {
 public:
  Deque();
  ~Deque();

  void PushFront(int data);
  void PushBack(int data);
  int PopFront();
  int PopBack();
  bool IsEmpty();

  void bufferExpansion();

 private:
  int head;
  int tail;
  int length;
  int *buffer;
};

Deque::Deque() : head(-1), tail(-1), length(2), buffer(new int[2]) {
  for (int i = 0; i < length; i++) {
    buffer[i] = 0;
  }
}

Deque::~Deque() {
  while (!IsEmpty()) {
    PopBack();
  }
  delete[] buffer;
}

void Deque::PushFront(int data) {
  if (IsEmpty()) {
    head = tail = 0;
    buffer[head] = data;
    return;
  }

  if (head == (tail + 1) % length) {
    bufferExpansion();
  }

  if (head == 0)
    head = length - 1;
  else
    head--;

  buffer[head] = data;
}

void Deque::PushBack(int data) {
  if (IsEmpty()) {
    head = tail = 0;
    buffer[head] = data;
    return;
  }

  if (head == (tail + 1) % length) {
    bufferExpansion();
  }

  tail = (tail + 1) % length;

  buffer[tail] = data;
}

int Deque::PopFront() {
  if (IsEmpty()) return -1;

  int tmpData = buffer[head];

  if (tail == head) {
    tail = head = -1;
    return tmpData;
  }

  head = (head + 1) % length;
  return tmpData;
}

int Deque::PopBack() {
  if (IsEmpty()) return -1;

  int tmpData = buffer[tail];

  if (tail == head) {
    tail = head = -1;
    return tmpData;
  }

  tail--;
  if (tail == -1) tail = length - 1;

  return tmpData;
}

bool Deque::IsEmpty() { return head == -1 && tail == -1; }

void Deque::bufferExpansion() {
  int new_length = length * 1.5;

  int *new_buffer = new int[new_length];
  for (int i = 0; i < new_length; i++) {
    new_buffer[i] = -1;
  }

  int index = head, new_tail = 0;

  while (index != tail) {
    new_buffer[new_tail] = buffer[index];
    index = (index + 1) % length;
    new_tail++;
  }
  new_buffer[new_tail] = buffer[index];

  delete[] buffer;

  buffer = new_buffer;
  length = new_length;
  tail = new_tail;
  head = 0;
}

int main() {
  Deque deque;

  int n = 0;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    int operation = 0, value = 0;
    std::cin >> operation >> value;

    switch (operation) {
      case 1: {
        deque.PushFront(value);
        break;
      }

      case 2: {
        int tmpVal = deque.PopFront();

        if (tmpVal != value) {
          std::cout << "NO" << std::endl;
          return 0;
        }
        break;
      }

      case 3: {
        deque.PushBack(value);
        break;
      }

      case 4: {
        int tmpVal = deque.PopBack();

        if (tmpVal != value) {
          std::cout << "NO" << std::endl;
          return 0;
        }
        break;
      }
    }
  }

  std::cout << "YES" << std::endl;
  return 0;
}