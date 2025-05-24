#include "BST.hpp"
#include <iostream>

int main() {
  BST<int> bst;
  bst.push(1);
  bst.push(2);
  bst.push(3);
  bst.push(4);

  bst.pop(4);
  bst.showBST();
}