#ifndef BST_HPP
#define BST_HPP

#include <iostream>

template <typename T>
class BST;

template <typename T>
class Node {
  friend class BST<T>;

public:
  T data;
  Node *left;
  Node *right;

  Node(const T &d) : data(d), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
private:
  Node<T> *root;
  void clear();
  void showInOrder(Node<T> *) const;
  void showPreOrder(Node<T> *) const;
  void showPostOrder(Node<T> *) const;
  int getNodeHeight(Node<T> *) const;

public:
  BST() : root(nullptr) {}
  ~BST() {}
  T getTop() const;
  bool isEmpty() const;
  void push(const T &);
  void pop();
  void showBST() const;
  int getHeight() const;
};

template <typename T>
bool BST<T>::isEmpty() const {
  if (root == nullptr) {
    return true;
  }
  return false;
}

template <typename T>
T BST<T>::getTop() const {
  return root->data;
}

template <typename T>
void BST<T>::push(const T &val) {
  Node<T> *newNode = new Node(val);
  if (isEmpty()) {
    root = newNode;
    return;
  }

  Node<T> *currentNode = root;
  while (true) {
    if (val < currentNode->data) {
      if (currentNode->left == nullptr) {
        currentNode->left = newNode;
        return;
      }
      currentNode = currentNode->left;
    } else {
      if (currentNode->right == nullptr) {
        currentNode->right = newNode;
        return;
      }
      currentNode = currentNode->right;
    }
  }
}

template <typename T>
void BST<T>::pop() {
}

template <typename T>
void BST<T>::showBST() const {
  std::cout << "Preorder: ";
  showPreOrder(root);
  std::cout << std::endl;

  std::cout << "Inorder: ";
  showInOrder(root);
  std::cout << std::endl;

  std::cout << "Postorder: ";
  showPostOrder(root);
  std::cout << std::endl;
}

template <typename T>
void BST<T>::showInOrder(Node<T> *current) const {
  if (current == nullptr)
    return;

  showInOrder(current->left);
  std::cout << current->data << ", ";
  showInOrder(current->right);
}

template <typename T>
void BST<T>::showPreOrder(Node<T> *current) const {
  if (current == nullptr)
    return;

  std::cout << current->data << ", ";
  showPreOrder(current->left);
  showPreOrder(current->right);
}

template <typename T>
void BST<T>::showPostOrder(Node<T> *current) const {
  if (current == nullptr)
    return;
  showPostOrder(current->left);
  showPostOrder(current->right);
  std::cout << current->data << ", ";
}
template <typename T>
int BST<T>::getHeight() const {
  return getNodeHeight(root);
}

template <typename T>
int BST<T>::getNodeHeight(Node<T> *node) const {
  if (node == nullptr)
    return 0;
  return 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
}

#endif
