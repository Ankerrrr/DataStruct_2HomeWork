#include "BST.hpp"
#include <iostream>

int main() {
  BST<int> bst;
  bst.push(1);
  bst.push(2);
  bst.push(3);
  bst.push(4);
  // bst.push(3);
  // bst.push(5);
  // bst.push(7);
  // bst.showBST();

  bst.pop(4);
  bst.showBST();
}