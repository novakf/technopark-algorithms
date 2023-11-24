/*
B. Дана последовательность, состоящая из символов '(' и ')'.
Требуется определить, является ли данная последовательность
правильной скобочной последовательностью. Длина исходной
последовательности ≤ 800000.
*/

#include <cassert>
#include <iostream>

class Stack {
public:
  explicit Stack(int bufferSize);
  ~Stack();
  void Push(char value);
  char Pop();
  bool IsEmpty() { return top == -1; }

private:
  char *buffer;
  int bufferSize;
  int top;
};

Stack::Stack(int bufferSize) : bufferSize(bufferSize), top(-1) {
  buffer = new char[bufferSize];
}

Stack::~Stack() { delete[] buffer; }

void Stack::Push(char value) {
  assert(top + 1 < bufferSize);
  buffer[++top] = value;
}

char Stack::Pop() {
  assert(top != -1);
  return buffer[top--];
}

int main() {
  std::string order;
  std::cin >> order;

  int length = order.length();
  Stack stack(length);

  for (char i = 0; i < length; i++) {
    if (order[i] == ')' && stack.IsEmpty()) {
      std::cout << "NO";
      return 0;
    }
    if (order[i] == '(')
      stack.Push(order[i]);
    if (order[i] == ')')
      stack.Pop();
  }

  if (stack.IsEmpty())
    std::cout << "YES";
  else
    std::cout << "NO";

  return 0;
}