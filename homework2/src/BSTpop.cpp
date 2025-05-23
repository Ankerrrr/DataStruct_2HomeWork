#include "BST.hpp"
#include <iostream>

int main() {
  BST<int> bst;
  bst.push(5);
  bst.push(3);
  bst.push(6);
  bst.showBST();

  bst.pop(5);
  bst.showBST();
}