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
  void pop(int key);
  void pop(int key, Node<T> *&);
  void showBST() const;
  int getHeight() const;
};

#include "BST.tpp"

#endif