#ifndef BST_TPP
#define BST_TPP

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
void BST<T>::pop(T key) {
  pop(key, root);
}

template <typename T>
void BST<T>::pop(T key, Node<T> *&current) {
  if (!current)
    return;
  if (key < current->data) {
    pop(key, current->left);
  } else if (key > current->data) {
    pop(key, current->right);
  } else { // ==
    if (!current->left && !current->right) {
      delete current;
      current = nullptr;
    } else if (!current->right) {
      Node<T> *temp = current;
      current = current->left;
      delete temp;
    } else if (!current->left) {
      Node<T> *temp = current;
      current = current->right;
      delete temp;
    } else {
      Node<T> *succer = current->right;
      while (succer->left)
        succer = succer->left;

      current->data = succer->data;
      pop(current->data, current->right);
    }
  }
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