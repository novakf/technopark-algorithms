/*
1_1. Хеш-таблица.
Реализуйте структуру данных типа “множество строк” на основе динамической
хеш-таблицы с открытой адресацией.
Для разрешения коллизий используйте квадратичное пробирование.
i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
*/

#include <iostream>
#include <vector>

const size_t DEFAULT_SIZE = 8;
const float MAX_ALPHA = 0.75;

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
      : size(0), table(initial_size) {}
  ~HashTable();

  bool Add(const T& key);
  bool Has(const T& key);
  bool Delete(const T& key);

  void show() {
    for (int i = 0; i < table.size(); i++) {
      if (table[i].status != HashTableCell::FIL)
        std::cout << (table[i].status == HashTableCell::DEL ? "DEL" : "NIL")
                  << " ";
      else
        std::cout << table[i].data << " ";
    }
    std::cout << std::endl;
  };

 private:
  void grow();

  struct HashTableCell {
    HashTableCell() : status(NIL) {}
    HashTableCell(const T& data) : data(data), status(FIL) {}
    T data;
    enum Status { NIL, DEL, FIL } status;
  };

  std::vector<HashTableCell> table;
  size_t size;
  Hasher hasher;
};

template <typename T, typename Hasher>
HashTable<T, Hasher>::~HashTable() {}

template <typename T, typename Hasher>
void HashTable<T, Hasher>::grow() {
  HashTable<std::string, StringHasher> newHashTable(table.size() * 2);

  for (int i = 0; i < table.size(); i++) {
    int hash = hasher(table[i].data) % newHashTable.table.size();
    if (table[i].status == HashTableCell::FIL) {
      newHashTable.Add(table[i].data);
    }
  }

  table = std::move(newHashTable.table);
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Add(const T& key) {
  size_t hash = hasher(key) % table.size();
  int i = 1;

  int deletedCellPos = -1;

  while (i != table.size()) {
    if (table[hash].data == key && table[hash].status == HashTableCell::FIL)
      return false;

    if (deletedCellPos == -1 && table[hash].status == HashTableCell::DEL)
      deletedCellPos = hash;

    if (table[hash].status == HashTableCell::NIL) break;

    hash = (hash + i + 1) % table.size();
    i++;
  }

  if (deletedCellPos != -1)
    table[deletedCellPos] = HashTableCell(key);
  else
    table[hash] = HashTableCell(key);
    
  size++;

  if (size > table.size() * MAX_ALPHA) grow();
  return true;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Has(const T& key) {
  size_t hash = hasher(key) % table.size();

  int i = 1;

  while (i != table.size()) {
    if (table[hash].data == key && table[hash].status == HashTableCell::FIL)
      return true;

    if (table[hash].status == HashTableCell::NIL) break;

    hash = (hash + i + 1) % table.size();
    i++;
  }

  return false;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Delete(const T& key) {
  size_t hash = hasher(key) % table.size();
  int i = 1;

  while (i != table.size()) {
    if (table[hash].status == HashTableCell::NIL) break;

    if (table[hash].data == key && table[hash].status != HashTableCell::DEL) {
      table[hash].status = HashTableCell::DEL;
      size--;
      return true;
    }

    hash = (hash + i + 1) % table.size();
    i++;
  }

  return false;
}

int main(int argc, const char* argv[]) {
  HashTable<std::string, StringHasher> hashTable;

  char operation;
  std::string key;

  while (std::cin >> operation >> key) {
    switch (operation) {
      case '+': {
        std::cout << (hashTable.Add(key) ? "OK" : "FAIL") << std::endl;
        // hashTable.show();
        break;
      }

      case '-': {
        std::cout << (hashTable.Delete(key) ? "OK" : "FAIL") << std::endl;
        // hashTable.show();
        break;
      }

      case '?': {
        std::cout << (hashTable.Has(key) ? "OK" : "FAIL") << std::endl;
        // hashTable.show();
        break;
      }
    }
  }

  return 0;
}
