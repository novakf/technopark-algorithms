/*
A. Дан массив, который получен путем нескольких циклических сдвигов
исходного отсортированного массива. Нужно найти индекс элемента, с
которого начинался исходный массив.
*/

#include <iostream>

int binary_search(int length, int *arr) {
  int first = 0, mid = 0;
  int last = length - 1;
  while (first < last) {
    mid = (first + last) / 2;
    if (arr[mid] > arr[last])
      first = mid + 1;
    else
      last = mid;
  }

  return first;
}

int main() {
  int length = 0, i = 0;
  std::cin >> length;

  int *arr = new int[length];
  for (i = 0; i < length; i++) {
    std::cin >> arr[i];
  }

  std::cout << binary_search(length, arr);

  delete[] arr;

  return 0;
}