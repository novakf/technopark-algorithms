/*
6.4. Дано множество целых чисел из [0..109] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие
параметры множества:
- 10% перцентиль
- медиана
- 90% перцентиль

Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию
Partition реализуйте методом прохода двумя итераторами от конца массива к
началу.
*/

#include <ctime>
#include <functional>
#include <iostream>

int getRandomValue(int left, int right) {
  return left + rand() % (right - left + 1);  // в интервале [left; right]
}

template <typename T, typename Comparator = std::less<T>>
int partition(T* arr, int left, int right, Comparator cmp = Comparator()) {
  int pivotPos = getRandomValue(left, right);

  T pivot = arr[pivotPos];
  std::swap(arr[left], arr[pivotPos]);

  int i = right;
  int j = right;

  while (true) {
    while (cmp(pivot, arr[j])) {
      j--;
      i--;
    }

    while (i > left && cmp(arr[i], pivot)) i--;

    std::swap(arr[i], arr[j]);

    if (i == left) return j;

    i--;
    j--;
  }
}

template <typename T, typename Comparator = std::less<T>>
T kthStatistic(T* arr, int k, int left, int right,
               Comparator cmp = Comparator()) {
  int pivotPos = partition(arr, left, right, cmp);

  while (pivotPos != k) {
    if (pivotPos > k) right = pivotPos - 1;
    if (pivotPos < k) left = pivotPos + 1;
    pivotPos = partition(arr, left, right, cmp);
  }

  return arr[pivotPos];
}

int main(int argc, const char* argv[]) {
  srand((unsigned int)time(nullptr));

  int n = 0;
  std::cin >> n;

  int* arr = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  std::cout << kthStatistic(arr, n * 0.1, 0, n - 1) << std::endl;
  std::cout << kthStatistic(arr, n * 0.5, 0, n - 1) << std::endl;
  std::cout << kthStatistic(arr, n * 0.9, 0, n - 1) << std::endl;

  delete[] arr;
  return 0;
}