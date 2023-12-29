#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>

const int FieldSize = 16;
const std::array<int, FieldSize> finishField = {1, 2,  3,  4,  5,  6,  7,  8,
                                                9, 10, 11, 12, 13, 14, 15, 0};

class GameState {
 public:
  GameState(const std::array<int, FieldSize> &field);

  bool IsComplete() const { return field == finishField; }
  bool IsSolvable() const;

  bool CanMoveLeft() const { return emptyPos % 4 != 3; }
  bool CanMoveRight() const { return emptyPos % 4 != 0; }
  bool CanMoveUp() const { return emptyPos < 12; }
  bool CanMoveDown() const { return emptyPos > 3; }

  GameState MoveLeft();
  GameState MoveRight();
  GameState MoveUp();
  GameState MoveDown();

  int getPriority(int pos) { return priority[pos];}
  int getEmptyPos() { return emptyPos; }

  bool operator==(const GameState &other) const { return field == other.field; }

 private:
  size_t getInvCount() const;

  int manhattanDistance(int start, int end) {
    int startX = start / 4;
    int startY = start % 4;
    int endX = end / 4;
    int endY = end % 4;

    return abs(startX - endX) + abs(startY - endY);
  }

  void updatePriorities() {
    for (int i = 0; i < FieldSize; i++) {
      priority[i] =
          manhattanDistance(emptyPos, i) + manhattanDistance(i, field[i] - 1);
    }
    priority[emptyPos] = -1;
  }

  std::array<int, FieldSize> field;
  std::array<float, FieldSize> priority;
  int emptyPos;

  friend struct GameStateHasher;
  friend std::ostream &operator<<(std::ostream &out, const GameState &state);
};

GameState::GameState(const std::array<int, FieldSize> &field) : field(field) {
  emptyPos = -1;
  for (int i = 0; i < FieldSize; i++) {
    if (field[i] == 0) {
      emptyPos = i;
    }
  }
  for (int i = 0; i < FieldSize; i++) {
    priority[i] =
        manhattanDistance(emptyPos, i) + manhattanDistance(i, field[i] - 1);
  }
  priority[emptyPos] = -1;

  assert(emptyPos != -1);
}

bool GameState::IsSolvable() const {
  int pos = -1;

  if (emptyPos < 4) pos = 1;
  if (emptyPos >= 4 && emptyPos < 8) pos = 2;
  if (emptyPos >= 8 && emptyPos < 12) pos = 3;
  if (emptyPos >= 12) pos = 4;

  return (getInvCount() + pos) % 2 == 0;
}

size_t GameState::getInvCount() const {
  size_t inv_count = 0;
  for (int i = 0; i < FieldSize - 1; i++) {
    for (int j = i + 1; j < FieldSize; j++) {
      if (field[i] > field[j] && field[i] && field[j]) inv_count++;
    }
  }
  return inv_count;
}

GameState GameState::MoveLeft() {
  assert(CanMoveLeft());

  GameState newState(*this);
  std::swap(newState.field[emptyPos], newState.field[emptyPos + 1]);
  newState.emptyPos++;

  newState.updatePriorities();

  return newState;
}

GameState GameState::MoveRight() {
  assert(CanMoveRight());

  GameState newState(*this);
  std::swap(newState.field[emptyPos], newState.field[emptyPos - 1]);
  newState.emptyPos--;

  newState.updatePriorities();

  return newState;
}

GameState GameState::MoveUp() {
  assert(CanMoveUp());

  GameState newState(*this);
  std::swap(newState.field[emptyPos], newState.field[emptyPos + 4]);
  newState.emptyPos += 4;

  newState.updatePriorities();

  return newState;
}

GameState GameState::MoveDown() {
  assert(CanMoveDown());

  GameState newState(*this);
  std::swap(newState.field[emptyPos], newState.field[emptyPos - 4]);
  newState.emptyPos -= 4;

  newState.updatePriorities();

  return newState;
}

struct GameStateHasher {
 public:
  size_t operator()(const GameState &state) const {
    size_t hash = 0;
    std::memcpy(&hash, state.field.data(), sizeof(hash));
    return hash;
  }
};

std::ostream &operator<<(std::ostream &out, const GameState &state) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out << static_cast<int>(state.field[i * 4 + j]) << ' ';
    }
    out << std::endl;
  }
  return out;
}

std::string GetSolution(const std::array<int, FieldSize> &field) {
  GameState startState(field);

  if (!startState.IsSolvable()) return "-1";

  std::unordered_map<GameState, char, GameStateHasher> visited;
  visited[startState] = 'S';

  std::queue<GameState> queue;
  queue.push(startState);

  while (true) {
    GameState state = queue.front();
    queue.pop();

    int emptyPos = state.getEmptyPos();

    int upPriority = state.CanMoveUp() ? state.getPriority(emptyPos + 4) : -1;
    int downPriority =
        state.CanMoveDown() ? state.getPriority(emptyPos - 4) : -1;
    int leftPriority =
        state.CanMoveLeft() ? state.getPriority(emptyPos + 1) : -1;
    int rightPriority =
        state.CanMoveRight() ? state.getPriority(emptyPos - 1) : -1;

    int highestPriority = std::max(std::max(leftPriority, rightPriority),
                                   std::max(upPriority, downPriority));

    std::cout << std::endl
              << "PR:" << highestPriority << " " << leftPriority << " "
              << rightPriority << " " << upPriority << " " << downPriority
              << " " << std::endl
              << std::endl;

    for (int i = 0; i < 16; i++) {
      std::cout << state.getPriority(i) << " ";
      if (i % 4 == 3) std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << state;

    if (state.IsComplete()) break;

    if (state.CanMoveLeft() && leftPriority == highestPriority) {
      GameState newState = state.MoveLeft();
      if (visited.find(newState) == visited.end()) {
        visited[newState] = 'L';
        queue.push(newState);
      }
      std::cout << "STEP: L" << std::endl;
      continue;
    }
    if (state.CanMoveUp() && upPriority == highestPriority) {
      GameState newState = state.MoveUp();
      if (visited.find(newState) == visited.end()) {
        visited[newState] = 'U';
        queue.push(newState);
      }
      std::cout << "STEP: U";
      continue;
    }
    if (state.CanMoveRight() && rightPriority == highestPriority) {
      GameState newState = state.MoveRight();
      if (visited.find(newState) == visited.end()) {
        visited[newState] = 'R';
        queue.push(newState);
      }
      std::cout << "STEP: R";
      continue;
    }
    if (state.CanMoveDown() && downPriority == highestPriority) {
      GameState newState = state.MoveDown();
      if (visited.find(newState) == visited.end()) {
        visited[newState] = 'D';
        queue.push(newState);
      }
      std::cout << "STEP: D";
      continue;
    }
  }

  std::string path;
  GameState state(finishField);

  std::cout << state << std::endl;
  while (visited[state] != 'S') {
    char move = visited[state];
    switch (move) {
      case 'L': {
        state = state.MoveRight();
        path += 'L';
        break;
      }
      case 'R': {
        state = state.MoveLeft();
        path += 'R';
        break;
      }
      case 'D': {
        state = state.MoveUp();
        path += 'D';
        break;
      }
      case 'U': {
        state = state.MoveDown();
        path += 'U';
        break;
      }
    }

    // std::cout << state << std::endl;
  }

  std::reverse(path.begin(), path.end());
  return path;
}

int main(int argc, const char *argv[]) {
  std::array<int, FieldSize> field;

  for (int i = 0; i < FieldSize; i++) {
    std::cin >> field[i];
  }

  std::string res = GetSolution(field);

  if (res != "-1")
    std::cout << res.size() << std::endl << res << std::endl;
  else
    std::cout << res << std::endl;
  return 0;
}