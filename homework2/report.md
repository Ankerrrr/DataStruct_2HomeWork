# 41243243

# 41243244

### 組員名單

- 黃安可 41243243
- 黃順駿 41243243

第二題報告

## 解題說明

本題有兩小題，

第一題要求實現一個 二元搜尋樹(BST)的基本架構，並且驗證 height/log2(n) 是否會接近於 2

第二小題為製作能夠刪除特定 key 值節點的功能，並且說明他的時間複雜度

### 解題策略

兩小題都是在 BST 的架構下運作的，因此我們首要的就是先做一個 BST 架構的基本功能

- push()
- pop()
- isEmpty()
- getTop()
- showBST()

  Preorder Inorder Postorder

在完成以上基本二元搜尋樹的功能後就能夠回答作業要求的兩個問題了

## 程式實作

### push()

```cpp
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
```

Push 用於將 Key 值放進 BST 內，本作業我們是採用迭代的方式，並使用樣板實作

程式邏輯是這樣的，假如 BST 樹是空的，那就直接將推入的值設成根結點就好了，假如並不是空的，BST 內有東西了，那就會不斷往下比較，推入的值比最上面的節點小就往左走，反之就往右走，不斷一層一層往下，直到最底部，就將新節點接入原有節點

### pop()

```cpp
template <typename T>
void BST<T>::pop(T key) {
  pop(key, root);
}
```

```cpp
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
```

為了達成作業二，這個 pop(T)用於將特定 KEY 值從 BST 內移除，為了練習不同的寫法，這個改為用遞迴方式，同樣使用樣板實作

遞迴版本需要引數包含 current Node 但使用者呼叫並不需要，因此我們使用多載的方式，使用兩個版本的 pop ，一個是僅需要使用者輸入 KEY 值的 pop(使用者版本)，他會呼叫真正實作 pop 功能兩個引數版本的遞迴 pop

在遞迴版本的內，一開始會接收兩個引數，一個是要刪除的 Key 值，一個則是 BST 的 root 節點，假如 Key 值比起目前節點小，那就會往左邊子節點遞迴呼叫，反之則為右子節點，不斷的運作並且比較是否和 KEY 值相等，假如終於比到相等也就是要刪除的節點，會判斷該節點的子節點樹，假如為 0 那僅需要移除該節點即可，假如為 1，則要把唯一的那個節點移上來替換成要刪除的節點，假如為 2，這裡有兩種實作方式，一種為 successor，一種為 predecessor，這裡我們用 successor 的方式實作，方法如下

1. 找出要刪除的節點右邊節點的最小值
2. 將找到的最小節點和要刪除的節點替換
3. 再將舊有的最小節點刪除

透過以上方法，就可以在不破壞 BST 構造的情況下，刪除特定節點，達成 pop(T)的功能

### showBST()

```cpp
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
```

```cpp
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
```

為了要檢視結果是否正確，所以要有顯示 BST 的功能，我們實作了 3 種 BST 的顯示方法， Inorder, Preorder, Postorder， 3 種差異在顯示的順序不一樣

- Inorder

  左子節點 > 中 > 右子節點

- Preorder

  中 > 左子節點 > 右子節點

- Postorder

  左子節點 > 右子節點 > 中

### getHeight()

```cpp
template <typename T>
int BST<T>::getHeight() const {
  return getNodeHeight(root);
}
```

```cpp
template <typename T>
int BST<T>::getNodeHeight(Node<T> *node) const {
  if (node == nullptr)
    return 0;
  return 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
}
```

同樣是因為遞迴需要 current 的引數，因此在另外用了一個使用者介面用於供使用者使用無引數的版本，getHeight() 用於計算從根結點開始的高度

getHeight() 函式會呼叫內部的遞迴函式 getNodeHeight(Node)，並開始從樹的根節點開始計算高度。這個遞迴函式會同時往左子樹和右子樹展開，一層一層地往下走

每當進入一個節點時，getNodeHeight 就會分別呼叫左子節點與右子節點的高度計算，然後取兩者的最大值

最後在一層一層從下將回傳值向上傳，最後得到高度

## 效能分析

## 測試與驗證

### 測試案例

### 編譯與執行指令

### 結論

## 申論及開發報告

### 選擇遞迴的原因
