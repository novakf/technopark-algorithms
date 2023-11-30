#include <functional>
#include <iostream>

template <typename T, typename Comparator = std::less<T>>
class BinaryTree {
  struct Node {
    Node* left;
    Node* right;
    T data;
    Node(T& value) : left(nullptr), right(nullptr), data(value) {}
  };

 public:
  BinaryTree() : root(nullptr), cmp(cmp = Comparator()) {}
  ~BinaryTree() { destroyTree(root); };

  void Add(T& value);
  bool checkIfDataSimilar();

 private:
  Node* root;
  Comparator cmp;

  void checkNodeData(Node* root, T value, bool& stopFlag);
  void addNode(Node*& node, T& data);
  void destroyTree(Node* node);
};

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::destroyTree(Node* node) {
  if (node) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::Add(T& data) {
  addNode(root, data);
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::addNode(Node*& node, T& data) {
  if (!node) {
    node = new Node(data);
    return;
  }

  if (cmp(node->data, data))
    addNode(node->right, data);
  else
    addNode(node->left, data);
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::checkNodeData(Node* node, T value,
                                              bool& stopFlag) {
  if (node == nullptr || stopFlag) {
    return;
  }

  if (node->data != value) stopFlag = true;
  checkNodeData(node->left, node->data, stopFlag);
  checkNodeData(node->right, node->data, stopFlag);
}

template <typename T, typename Comparator>
bool BinaryTree<T, Comparator>::checkIfDataSimilar() {
  bool stopFlag = false;
  checkNodeData(root, root->data, stopFlag);
  return stopFlag;
}

int main(int argc, const char* argv[]) {
  BinaryTree<int> tree;
  int val;

  while (std::cin >> val) {
    tree.Add(val);
  }

  if (tree.checkIfDataSimilar())
    std::cout << '0';
  else
    std::cout << '1';

  return 0;
}
