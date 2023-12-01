/*
4_1. Солдаты АВЛ.
*/

#include <functional>
#include <iostream>

template <typename T>
class DefaultMoreComparator {
 public:
  bool operator()(const T &first, const T &second) { return first > second; }
};

template <typename T, typename Comparator = std::less<T>>
class AvlTree {
  struct Node {
    Node(const T &data)
        : data(data), left(nullptr), right(nullptr), height(1), nodesCount(1) {}

    T data;
    Node *left;
    Node *right;
    size_t height;
    size_t nodesCount;
  };

 public:
  AvlTree() : root(nullptr), cmp(Comparator()) {}
  ~AvlTree() { destroyTree(root); }

  void Add(const T &data) { root = addInternal(root, data); }
  void Delete(const T &data) { root = deleteInternal(root, data); }
  bool Has(const T &data);

  T getDataByPos(int pos) { return getData(root, pos)->data; }
  int getPosByData(T data) { return getPos(root, data); }

  void showTree() { show(root); }

 private:
  void show(Node *node);

  Node *getData(Node *node, int pos);
  int getPos(Node *node, T data);

  void destroyTree(Node *node);
  Node *deleteInternal(Node *node, const T &data);

  Node *findAndRemoveMin(Node *left, Node *right);
  Node *findAndRemoveMax(Node *left, Node *right);
  Node *removeMin(Node *node);
  Node *removeMax(Node *node);

  Node *addInternal(Node *node, const T &data);

  size_t getHeight(Node *node) { return node ? node->height : 0; }
  size_t getNodesCount(Node *node) { return node ? node->nodesCount : 0; }

  void fixHeight(Node *node);
  void fixCount(Node *node);

  int getBalance(Node *node);
  Node *doBalance(Node *node);

  Node *rotateLeft(Node *node);
  Node *rotateRight(Node *node);

  Node *root;
  Comparator cmp;
};

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::show(Node *node) {
  if (!node) return;

  std::cout << node->data << " ";
  show(node->left);
  show(node->right);
}

template <typename T, typename Comparator>
bool AvlTree<T, Comparator>::Has(const T &data) {
  Node *tmp = root;
  while (tmp) {
    if (tmp->data == data)
      return true;
    else if (cmp(tmp->data, data))
      tmp = tmp->right;
    else
      tmp = tmp->left;
  }
  return false;
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node *AvlTree<T, Comparator>::getData(
    Node *node, int pos) {
  size_t nodesCountInLeftNode = getNodesCount(node->left);

  if (nodesCountInLeftNode == pos) return node;

  if (cmp(nodesCountInLeftNode, pos)) {
    return getData(node->left, pos);
  }

  return getData(node->right, pos - nodesCountInLeftNode - 1);
}

template <typename T, typename Comparator>
int AvlTree<T, Comparator>::getPos(Node *node, T data) {
  if (!node) return 0;

  if (cmp(data, node->data)) {
    return getPos(node->left, data);
  }

  return getNodesCount(node->left) + 1 + getPos(node->right, data);
}

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::destroyTree(Node *node) {
  if (node) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node *AvlTree<T, Comparator>::deleteInternal(
    Node *node, const T &data) {
  if (!node) return nullptr;

  if (cmp(data, node->data))
    node->left = deleteInternal(node->left, data);
  else if (cmp(node->data, data))
    node->right = deleteInternal(node->right, data);
  else {
    Node *left = node->left;
    Node *right = node->right;

    delete node;

    if (!right) return left;
    if (!left) return right;

    if (right->height > left->height)
      // минимальный в правом поддереве
      return findAndRemoveMin(left, right);
    else
      // максимальный в левом поддереве
      return findAndRemoveMax(left, right);
  }

  return doBalance(node);
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node *AvlTree<T, Comparator>::findAndRemoveMin(
    Node *left, Node *right) {
  Node *minNode = right;
  while (minNode->left) minNode = minNode->left;

  minNode->right = removeMin(right);
  minNode->left = left;

  return doBalance(minNode);
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node *AvlTree<T, Comparator>::removeMin(
    Node *node) {
  if (!node->left) return node->right;
  node->left = removeMin(node->left);
  return doBalance(node);
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node *AvlTree<T, Comparator>::findAndRemoveMax(
    Node *left, Node *right) {
  Node *maxNode = left;
  while (maxNode->right) maxNode = maxNode->right;

  maxNode->left = removeMax(left);
  maxNode->right = right;

  return doBalance(maxNode);
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node *AvlTree<T, Comparator>::removeMax(
    Node *node) {
  if (!node->right) return node->left;
  node->right = removeMax(node->right);
  return doBalance(node);
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node *AvlTree<T, Comparator>::addInternal(
    Node *node, const T &data) {
  if (!node) return new Node(data);

  if (cmp(data, node->data))
    node->left = addInternal(node->left, data);
  else
    node->right = addInternal(node->right, data);

  return doBalance(node);
}

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::fixHeight(Node *node) {
  node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

template <typename T, typename Comparator>
void AvlTree<T, Comparator>::fixCount(Node *node) {
  node->nodesCount = getNodesCount(node->left) + getNodesCount(node->right) + 1;
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node *AvlTree<T, Comparator>::rotateLeft(
    Node *node) {
  Node *tmp = node->right;
  node->right = tmp->left;
  tmp->left = node;
  fixHeight(node);
  fixHeight(tmp);
  fixCount(node);
  fixCount(tmp);
  return tmp;
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node *AvlTree<T, Comparator>::rotateRight(
    Node *node) {
  Node *tmp = node->left;
  node->left = tmp->right;
  tmp->right = node;
  fixHeight(node);
  fixHeight(tmp);
  fixCount(node);
  fixCount(tmp);
  return tmp;
}

template <typename T, typename Comparator>
int AvlTree<T, Comparator>::getBalance(Node *node) {
  return getHeight(node->right) - getHeight(node->left);
}

template <typename T, typename Comparator>
typename AvlTree<T, Comparator>::Node *AvlTree<T, Comparator>::doBalance(
    Node *node) {
  fixHeight(node);
  fixCount(node);
  switch (getBalance(node)) {
    case 2: {
      if (getBalance(node->right) < 0) node->right = rotateRight(node->right);
      return rotateLeft(node);
    }
    case -2: {
      if (getBalance(node->left) > 0) node->left = rotateLeft(node->left);
      return rotateRight(node);
    }
    default:
      return node;
  }
}

int main(int argc, const char *argv[]) {
  AvlTree<int, DefaultMoreComparator<int>> tree;
  int val = 0;
  int length = 0;
  std::cin >> length;

  int operation;
  int key;

  for (int i = 0; i < length; i++) {
    std::cin >> operation >> val;
    switch (operation) {
      case 1: {
        std::cout << tree.getPosByData(val) << std::endl;
        tree.Add(val);
        break;
      }

      case 2: {
        tree.Delete(tree.getDataByPos(val));
        break;
      }
    }
    // tree.showTree();
    // std::cout << std::endl;
  }

  return 0;
}
