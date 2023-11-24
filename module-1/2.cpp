/*
2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел
B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс k
минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i].
Если такого элемента нет, выведите n. n, m ≤ 10000. Требования:  Время работы
поиска k для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для
каждого B[i] сначала нужно определить диапазон для бинарного поиска размером
порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный
поиск.
*/

#include <iostream>

int binary_search(int el, int *arr, int first, int last) {
  int mid = 0;
  while (first < last) {
    mid = (first + last) / 2;
    if (arr[mid] < el)
      first = mid + 1;
    else
      last = mid;
  }

  return first;
}

int exponential_search(int el, int *arr, int length) {
  int left = 0, right = 1;

  if (arr[0] >= el) return 0;

  while (right != length) {
    if (arr[right] >= el) break;

    left = right;
    right *= 2;

    if (right > length) right = length;
  }

  return binary_search(el, arr, left, right);
}

int main() {
  int n = 0, m = 0, i = 0;
  std::cin >> n >> m;

  int *arr1 = new int[n];
  for (i = 0; i < n; i++) {
    std::cin >> arr1[i];
  }

  int *arr2 = new int[m];
  for (i = 0; i < m; i++) {
    std::cin >> arr2[i];
  }

  for (i = 0; i < m; i++) {
    std::cout << exponential_search(arr2[i], arr1, n);
    (i != m - 1) && std::cout << ' ';
  }

  delete[] arr1;
  delete[] arr2;

  return 0;
}