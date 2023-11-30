/*
2_2. Обход дерева в порядке pre-order
*/

#include <functional>
#include <iostream>
#include <stack>

template <typename T, typename Comparator = std::less<T>>
class BinaryTree {
  struct Node {
    Node* left;
    Node* right;
    T data;
    Node(T& value) : left(nullptr), right(nullptr), data(value) {}
    Node() : left(nullptr), right(nullptr) {}
  };

 public:
  BinaryTree() : root(nullptr), cmp(Comparator()) {}
  ~BinaryTree();

  void Add(T& value);
  void showTree();

 private:
  Node* root;
  Comparator cmp;
};

template <typename T, typename Comparator>
BinaryTree<T, Comparator>::~BinaryTree() {
  if (!root) return;

  std::stack<Node*> nodesStack;
  nodesStack.push(root);

  while (!nodesStack.empty()) {
    Node* node = nodesStack.top();
    nodesStack.pop();

    if (node->right) nodesStack.push(node->right);

    if (node->left) nodesStack.push(node->left);

    delete node;
  }
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::showTree() {
  if (!root) return;

  std::stack<Node*> nodesStack;
  nodesStack.push(root);

  while (!nodesStack.empty()) {
    Node* node = nodesStack.top();
    nodesStack.pop();
    std::cout << node->data << " ";

    if (node->right) nodesStack.push(node->right);

    if (node->left) nodesStack.push(node->left);
  }
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::Add(T& data) {
  if (root == nullptr) {
    root = new Node(data);
    return;
  }

  Node* node = root;

  while (node != nullptr) {
    if (cmp(node->data, data)) {
      if (node->right == nullptr) {
        node->right = new Node(data);
        return;
      }
      node = node->right;
    } else {
      if (node->left == nullptr) {
        node->left = new Node(data);
        return;
      }
      node = node->left;
    }
  }

  node->data = data;
}

int main(int argc, const char* argv[]) {
  BinaryTree<int> tree;
  int val = 0;
  int length = 0;
  std::cin >> length;

  for (int i = 0; i < length; i++) {
    std::cin >> val;
    tree.Add(val);
  }

  tree.showTree();

  return 0;
}
