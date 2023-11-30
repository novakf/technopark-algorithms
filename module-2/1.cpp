#include <iostream>
#include <vector>

const size_t DEFAULT_SIZE = 8;
const float MAX_ALPHA = 2;

template <typename T>
struct HashTableNode {
  HashTableNode() : next(nullptr) {}
  HashTableNode(const T& data, HashTableNode<T>* next)
      : data(data), next(next) {}

  T data;
  HashTableNode* next;
};

class StringHasher {
 public:
  StringHasher(size_t prime = 71) : prime(prime) {}

  size_t operator()(const std::string& str) {
    size_t hash = 0;
    for (int i = 0; i < str.size(); i++) {
      hash = hash * prime + str[i];
    }
    return hash;
  }

 private:
  size_t prime;
};

template <typename T, typename Hasher>
class HashTable {
 public:
  HashTable(size_t initial_size = DEFAULT_SIZE)
      : size(0), table(initial_size, nullptr) {}
  ~HashTable();

  bool Add(const T& key);
  bool Has(const T& key);
  bool Delete(const T& key);

 private:
  void grow();

  std::vector<HashTableNode<T>*> table;
  size_t size;
  Hasher hasher;
};

template <typename T, typename Hasher>
HashTable<T, Hasher>::~HashTable() {
  for (int i = 0; i < table.size(); i++) {
    HashTableNode<T>* node = table[i];

    while (node != nullptr) {
      HashTableNode<T>* next = node->next;
      delete node;
      node = next;
    }
  }
}

template <typename T, typename Hasher>
void HashTable<T, Hasher>::grow() {
  std::vector<HashTableNode<T>*> newTable(table.size() * 2, nullptr);

  for (int i = 0; i < table.size(); i++) {
    HashTableNode<T>* node = table[i];

    while (node != nullptr) {
      HashTableNode<T>* next = node->next;
      size_t newHash = hasher(node->data) % newTable.size();
      node->next = newTable[newHash];
      newTable[newHash] = node;
      node = next;
    }

    table = std::move(newTable);
  }
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Add(const T& key) {
  if (size > table.size() * MAX_ALPHA) grow();

  size_t hash = hasher(key) % table.size();
  HashTableNode<T>* node = table[hash];

  while (node != nullptr) {
    if (node->data == key) {
      return false;
    }
    node = node->next;
  }

  table[hash] = new HashTableNode<T>(key, table[hash]);
  size++;
  return true;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Has(const T& key) {
  size_t hash = hasher(key) % table.size();
  HashTableNode<T>* node = table[hash];

  while (node != nullptr) {
    if (node->data == key) {
      return true;
    }
    node = node->next;
  }

  return false;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Delete(const T& key) {
  size_t hash = hasher(key) % table.size();

  HashTableNode<T>* node = table[hash];
  HashTableNode<T>* prev = nullptr;

  while (node != nullptr) {
    if (node->data == key) break;
    prev = node;
    node = node->next;
  }

  if (node == nullptr) return false;

  if (prev == nullptr) {
    table[hash] = node->next;
  } else {
    prev->next = node->next;
  }

  delete node;
  size--;
  return true;
}

int main(int argc, const char* argv[]) {
  HashTable<std::string, StringHasher> hashTable;

  char operation;
  std::string key;

  while (std::cin >> operation >> key) {
    switch (operation) {
      case '+': {
        std::cout << (hashTable.Add(key) ? "OK" : "FAIL") << std::endl;
        break;
      }

      case '-': {
        std::cout << (hashTable.Delete(key) ? "OK" : "FAIL") << std::endl;
        break;
      }

      case '?': {
        std::cout << (hashTable.Has(key) ? "OK" : "FAIL") << std::endl;
        break;
      }
    }
  }

  return 0;
}