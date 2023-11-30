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
  int getMinHeight();

 private:
  Node* root;
  Comparator cmp;

  void checkNodeData(Node* root, T value, int& height, int& count);
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
void BinaryTree<T, Comparator>::checkNodeData(Node* node, T value, int& height,
                                              int& count) {
  if (node == nullptr) {
    if (count < height || (height == 0)) {
      height = count;
      count = 0;
    }
    return;
  }

  count++;
  std::cout << count << " " << height << std::endl; 

  checkNodeData(node->left, node->data, height, count);
  checkNodeData(node->right, node->data, height, count);
}

template <typename T, typename Comparator>
int BinaryTree<T, Comparator>::getMinHeight() {
  int height = 0;
  int count = 0;
  checkNodeData(root, root->data, height, count);
  return ++height;
}

int main(int argc, const char* argv[]) {
  BinaryTree<int> tree;
  int val;

  while (std::cin >> val) {
    tree.Add(val);
  }

  std::cout << tree.getMinHeight();

  return 0;
}
