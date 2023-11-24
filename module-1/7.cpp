/*
7_2. LSD для long long.
Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше
10^6. Отсортировать массив методом поразрядной сортировки LSD по байтам.
*/

#include <cassert>
#include <iostream>

int extractByte(unsigned long long element, int pos) {
  return ((element >> (8 * pos)) & 255);
}

void countingSort(unsigned long long *arr, int length, int pos) {
  assert(arr != nullptr);
  assert(length > 0);

  int minVal = extractByte(arr[0], pos);
  int maxVal = extractByte(arr[0], pos);

  for (int i = 1; i < length; i++) {
    minVal = std::min(minVal, extractByte(arr[i], pos));
    maxVal = std::max(maxVal, extractByte(arr[i], pos));
  }

  int bufferSize = maxVal - minVal + 1;
  int *buffer = new int[bufferSize]();

  for (int i = 0; i < length; i++) {
    buffer[extractByte(arr[i], pos) - minVal]++;
  }

  unsigned long long *sortedArr = new unsigned long long[length]();

  for (int i = 1; i < bufferSize; i++) {
    buffer[i] += buffer[i - 1];
  }

  for (int i = length - 1; i >= 0; i--) {
    int bufferPositon = extractByte(arr[i], pos) - minVal;
    buffer[bufferPositon]--;
    sortedArr[buffer[bufferPositon]] = arr[i];
  }

  for (int i = 0; i < length; i++) {
    arr[i] = sortedArr[i];
  }

  delete[] buffer;
  delete[] sortedArr;
}

void LSDSort(unsigned long long *arr, int length) {
  for (int i = 0; i < 8; i++) {
    countingSort(arr, length, i);
  }
}

int main(int args, const char *argv[]) {
  int n = 0;
  std::cin >> n;

  unsigned long long *arr = new unsigned long long[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  LSDSort(arr, n);

  for (int i = 0; i < n; i++) {
    std::cout << arr[i];
    (i != n - 1) && std::cout << ' ';
  }

  delete[] arr;
  return 0;
}