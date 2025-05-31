# 41243243

# 41243244

### 組員名單

- 黃安可 41243243
- 黃順駿 41243244

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

在遞迴版本的內，一開始會接收兩個引數，一個是要刪除的 Key 值，一個則是 BST 的 root 節點，假如 Key 值比起目前節點小，那就會往左邊子節點遞迴呼叫，反之則為右子節點，不斷的運作並且比較是否和 KEY 值相等，假如終於比到相等也就是要刪除的節點，會判斷該節點的子節點樹

- 假如子節點數為 0

  僅須直接移除該節點即可

- 假如子節點數為 1

  要把唯一的那個節點移上來替換成要刪除的節點

- 假如子節點數為 2

  一種為 successor，一種為 predecessor，這裡我們用 successor 的方式實作，方法如下

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

### 時間複雜度

1.  push()

    取決於樹的形狀，若樹非常平衡，時間複雜度為 **O(log n)**，因為每一次的選擇都會將搜尋範圍縮小一半。但若樹退化成鏈狀結構（例如每次插入的節點都比前一個大或小），則時間複雜度會退化為 **O(n)**，因為需要從根節點一路往下走到最底部才能完成插入。

    最好情況:O(log n)
    最壞情況:O(n)

2.  Pop(T)

    Pop(T)的時間複雜一樣是取決於樹的形狀，如果樹是平衡的，
    時間複雜度為 **o(log n)**，
    和 push 一樣每一次的選擇都會將搜尋範圍減少一半。
    但一樣樹若是不平衡甚至於退化成鏈狀結構，複雜度會提升到 **O(n)**，因為將需要每一個節點都搜尋過一遍，失去了 BST 的特性。

    最好情況:O(log n)

    最壞情況:O(n)

### 空間複雜度

1.  push()

    在 push() 內，會占用一個 Node 節點的空間，，因此僅考慮 Push 函式，空間複雜度為，**O(1)**

    時間複雜度:O(1)

2.  pop(T)

    pop() 採用遞迴實作，因此其空間複雜度取決於遞迴深度，即樹的高度。在最佳情況（例如平衡的 BST）下，遞迴深度為 O(log n)，空間複雜度也為 O(log n)。但在最壞情況下（如退化為鏈狀結構），遞迴深度為 O(n)，空間複雜度也會退化為 O(n)

    最好情況:O(log n)
    最壞情況:O(n)

## 測試與驗證

本小節將實證作業第一、二小題題目要求

1. 亂數和 height/log2(n)的關係
2. Pop(T) 所需的時間複雜度

### 測試案例

### 一、 亂數和 height/log2(n)的關係

#### 完美二元樹

```cpp
   BST<int> bst;
   std::vector<float> vectorScore;
   bst.push(2);
   bst.push(1);
   bst.push(3);
   float score = cacu(bst.getHeight(), 3);
   vectorScore.push_back(score);
   std::cout << score << std::endl;
   std::cout << "Avg: " << avg(vectorScore) << std::endl;
   std::cout << "Mid: " << mid(vectorScore) << std::endl;

```

```Plaintext
1.26186
Avg: 1.26186
Mid: 1.26186
```

以上程式我們建了一個完美二元樹，其大致長得像這樣

```Plaintext
    2
  /   \
 1     3
```

套入公式 得到 1.26186

```Plaintext
      4
    /   \
   2     6
  / \   / \
 1   3 5   7
```

套入公式 得到 1.06862

整理出以下表格:

| 節點數 (n) | 樹高 (Height) | log₂(n) | Height / log₂(n) |
| ---------- | ------------- | ------- | ---------------- |
| 3          | 2             | 1.58496 | 1.26186          |
| 7          | 3             | 2.80735 | 1.06862          |

所以刻意製造的完美二元樹會越來越趨近於 1

---

#### 極端二元樹

```cpp
  BST<int> bst;
  std::vector<float> vectorScore;
  bst.push(1);
  bst.push(2);
  bst.push(3);
  bst.push(4);
  bst.push(5);
  bst.push(6);
  bst.push(7);
  bst.push(8);
  bst.push(9);
  bst.push(10);
  bst.push(11);
  bst.push(12);
```

結果:

```Plaintext
Avg: 3.34732
Mid: 3.34732
```

```Plaintext
 1
  \
   2
    \
     3
      \
       ...
```

height/log2(n)

由於已退化成了鏈結串列，隨著 height 不斷增加，分子上升的比分母還要快
，最終呈現發散，趨近於無限大。

#### 隨機亂數產生

```cpp
int main() {
  srand(time(NULL));
  std::vector<float> vectorScore;

  int testIndex = 0;
  int testValue[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 50000, 60000, 70000, 80000, 90000, 100000};
  int length = sizeof(testValue) / sizeof(testValue[0]);

  for (; testIndex < length; ++testIndex) {
    int i = testValue[testIndex];
    BST<int> bst;
    for (int j = 0; j < i; j += 1) {
      bst.push(generateNumber(randMax));
    }
    std::cout << "i=" << i << ": ";
    float score = cacu(bst.getHeight(), i);
    vectorScore.push_back(score);
    std::cout << score << std::endl;
  }
  std::cout << "Avg: " << avg(vectorScore) << std::endl;
  std::cout << "Mid: " << mid(vectorScore) << std::endl;
}
```

我們使用了 CPP 標準函式庫的 Rand 作為亂數產生 ，並使用 time 當作亂數種子(Srand)

以上程式執行結果如下

```cpp
const int randMax = 2000;
```

```Plaintext
i=100: 2.40824
i=500: 2.45377
i=1000: 2.00687
i=2000: 2.37101
i=3000: 2.33751
i=4000: 2.08929
i=5000: 2.2787
i=6000: 2.46997
i=7000: 2.66184
i=8000: 2.39091
i=9000: 2.66449
i=10000: 2.55875
i=50000: 4.42035
i=60000: 4.28409
i=70000: 4.41129
i=80000: 5.03447
i=90000: 5.59011
i=100000: 5.77978
Avg: 3.23397
Mid: 2.55875
```

可以看到隨著 i 的提升 ， height/log2(n) 的值也隨之提升

推測為當亂數範圍變大時，生成的節點值分佈更分散，衝突與重複值的機率降低，因此 BST 更接近平衡樹，height/log2(n) 更趨近於理想值。

---

```cpp
const int randMax = 10000;
```

```Plaintext
i=100: 2.40824
i=500: 1.8961
i=1000: 2.70927
i=2000: 2.09743
i=3000: 2.25094
i=4000: 2.34001
i=5000: 2.03455
i=6000: 2.3903
i=7000: 2.42697
i=8000: 2.15953
i=9000: 2.35998
i=10000: 2.33298
i=50000: 2.56252
i=60000: 2.64606
i=70000: 2.73376
i=80000: 2.70142
i=90000: 2.79505
i=100000: 3.0103
Avg: 2.43641
Mid: 2.40824
```

這次我們把亂數產生的最大值從原本的 2000 提升到 10000，i 跟隨結果的提升也有所減少了

#### 結論

可見亂數產生確實會讓結果落在 2 附近，但由於其不如完美二元樹那樣平衡，
因此高度仍有可能偏高，使得比值無法趨近於 1。
這也說明了隨機插入所建立的 BST 結構雖然在平均情況下具有對數性質，但仍可能出現高度偏離理想值的情況，
導致該比值接近 2

---

### 二、 pop(T) 的時間複雜度

以下我們將測試 pop(T)操作的時間複雜度

已經先在程式內加上輸出，已用於觀察程式執行

```cpp
template <typename T>
void BST<T>::pop(T key, Node<T> *&current) {
  if (!current)
    return;
  if (key < current->data) {
    std::cout << "is going to Left" << std::endl; // test
    pop(key, current->left);
  } else if (key > current->data) {
    std::cout << "is going to Right" << std::endl; // test
    pop(key, current->right);
  } else {                             // ==
    std::cout << "equal" << std::endl; // test
    if (!current->left && !current->right) {
      std::cout << "no child node" << std::endl; // test
      delete current;
      current = nullptr;
    } else if (!current->right) {
      std::cout << "one node" << std::endl; // test
      Node<T> *temp = current;
      current = current->left;
      delete temp;
    } else if (!current->left) {
      std::cout << "one node" << std::endl; // test
      Node<T> *temp = current;
      current = current->right;
      delete temp;
    } else {
      std::cout << "second child node(succer)" << std::endl; // test
      Node<T> *succer = current->right;
      while (succer->left) {
        std::cout << "succer: find min node" << std::endl; // test
        succer = succer->left;
      }
      current->data = succer->data;
      std::cout << "remove min leaf Node: " << std::endl; // test
      pop(current->data, current->right);
    }
  }
}
```

#### 完美二元樹

先建構一個範例完美二元素

```Plaintext
    2
  /   \
 1     3
```

若執行 pop(3)，需要經過 2 > 3 ，

(n = 3) 經過兩個節點

再看更大的例子：

```Plaintext
      4
    /   \
   2     6
  / \   / \
 1   3 5   7
```

```cpp
BST<int> bst;
bst.push(4);
bst.push(2);
bst.push(6);
bst.push(1);
bst.push(3);
bst.push(5);
bst.push(7);

bst.pop(7);
```

```Plaintext
is going to Right
is going to Right
equal
no child node
```

刪除節點 7 需要經過 4 > 6 > 7

(n = 7) 經過 3 個節點

#### 變成串狀二元樹

```Plaintext
 1
  \
   2
    \
     3
      \
       4
```

```cpp
BST<int> bst;
bst.push(1);
bst.push(2);
bst.push(3);
bst.push(4);

bst.pop(4);
bst.showBST();
```

```Plaintext
is going to Right
is going to Right
is going to Right
equal
no child node
```

如要刪除 4 ， 需要經過 1>2>3>4
(n = 4) 經過 4 個節點

---

```Plaintext
 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6
```

如要刪除 6 ， 需要經過 1>2>3>4>5>6
(n = 6) 經過 6 個節點

### 結論

將上述兩種極端情況整理成表格

| 節點數 $n$ | 樹的結構類型 | pop 的目標節點 | 經過節點數 | 說明                  |
| ---------- | ------------ | -------------- | ---------- | --------------------- |
| 3          | 完美二元樹   | 3              | 2          | 2 → 3                 |
| 7          | 完美二元樹   | 7              | 3          | 4 → 6 → 7             |
| 4          | 串狀（右斜） | 4              | 4          | 1 → 2 → 3 → 4         |
| 6          | 串狀（右斜） | 6              | 6          | 1 → 2 → 3 → 4 → 5 → 6 |

得出結論:完美二元樹 pop 時間複雜度將會是 log(n)+1，
若是變成了串狀則會成為 n

最好情況:O(log n)  
最壞情況:O(n)

### 編譯與執行指令

#### (a)小題

編譯

```Bash
g++ -g BSTverify.cpp -o ./BSTverify.exe
```

執行

```bash
./BSTverify.exe
```

#### (b)小題

編譯

```Bash
g++ -g BSTpop.cpp -o ./BSTpop.exe
```

執行

```Bash
./BSTpop.exe
```

## 申論及開發報告

### 學習收穫

透過本次作業，我們對以下幾個重點有了更深刻的理解：

- BST 的實作細節：像是節點的插入與刪除，背後其實有很多必須考慮，不能只想理想情況。

- 平衡 BST 的重要性：雖然這題沒有要求 AVL Tree 或 Red-Black Tree，但我們已能體會平衡的重要性，若未來要實作更高效能的搜尋樹，這會是一個重要的方向。

- 實作與理論結合的重要性：從程式設計中實際驗證 height/log2(n) 的趨勢，比單看教科書更能深刻理解其理論意涵。

### 心得

#### 黃安可心得

<<<<<<< HEAD
這個作業要用到很多以前資料結構學過的東西，鏈結串列、分析時間複雜度、證明，還有二元搜尋樹 successor 和 predecessor ，完成了之後我感覺已經把從前到現在的資料結構都複習過了一遍，我覺得再 pop()用的遞迴的部分最為燒腦，我們想了很久查了很久才做出來，我覺得做完這個作業資料結構能力又變得更強了，好玩!!

#### 黃順駿心得

透過這次的作業，我們深入了解了 Binary Search Tree（二元搜尋樹） 的基本運作原理與實作方法。從節點的插入（push）、刪除（pop），到三種遍歷方式（Inorder、Preorder、Postorder）以及高度計算，讓我們實際體驗到資料結構在程式設計中的重要性。

> > > > > > > 7596a73d83e26a5148f7e9f044d61f0b7e9ad1b1
