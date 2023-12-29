#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>

int manhattanDistance(int start, int end) {
  int startX = start / 4;
  int startY = start % 4;
  int endX = end / 4;
  int endY = end % 4;

  return abs(startX - endX) + abs(startY - endY);
}

int main(int argc, const char *argv[]) {
  int a;
  int b;

  std::cin >> a;
  std::cin >> b;


  std::cout << manhattanDistance(a, b);
  return 0;
}