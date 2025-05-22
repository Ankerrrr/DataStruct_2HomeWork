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

public:
  BST() : root(nullptr) {}
  ~BST() {}
  T getTop() const;
  bool isEmpty() const;
  void push(const T &);
  void pop();
  void showBST();
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
void BST<T>::showBST() {
  showInOrder(root);
}

template <typename T>
void BST<T>::showInOrder(Node<T> *current) const {
  if (current == nullptr)
    return;

  showInOrder(current->left);
  std::cout << current->data << ", ";
  showInOrder(current->right);
}

#endif
