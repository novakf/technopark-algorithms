/*
1.1 Подсчитать кол-во единичных бит в входном числе ,
стоящих на четных позициях. Позиции битов нумеруются с 0.
*/

#include <cassert>
#include <iostream>

int even_bit_count(int num) {
  assert(num >= 0);
  int bit = 0, position = 0, count = 0;

  while (num != 0) {
    bit = num & 1;
    if (bit == 1)
      count++;
    position++;
    num >>= 2;
  }

  return count;
}

int main() {
  int num = 0;
  std::cin >> num;
  std::cout << even_bit_count(num);
  return 0;
}