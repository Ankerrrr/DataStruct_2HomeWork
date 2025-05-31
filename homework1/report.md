# 41243243

# 41243244

### 組員名單

- 黃安可 41243243
- 黃順駿 41243243

第一題報告

## Max / min Heap 作業 2_1

## 解題說明

本題要求實作一個最小優先佇列（Min Priority Queue）的資料結構，並實作出最小堆積樹(min Heap)和最大堆積樹(Max Heap)。為了驗證 minHeap 的功能是否正確，我們將使用該堆積樹進行排序，並透過排序後的結果來檢驗其正確性

## 解題策略

### 架構

符合題目要求最小優先佇列提供下列功能

- isEmpty()
- getTop()
- push()
- pop()

依照題目要求我們將課本提供的範例功能定義於 **minPQ.hpp**，並在**minAndMax_heap.hpp**宣告繼承 minPQ，繼承後的 minAndMax_heap.hpp，會在另外增加兩個函式，以維護堆積樹的架構

- shiftUP
- shiftDown

這兩個函式定義於 minAndMax_heap.hpp 並實作於 minAndMax_heap.tpp

### min and Max heap

為了要達成同時擁有 minHeap 和 maxHeap ，但又不想要為此寫兩份程式只為了少許的不同，我們設計 minAndMax_heap 能同時達成如檔名一樣能夠達成兩種模式，因此在一開始建構元中，必須要先設定要使用的模式，如以下程式

```cpp
minAndMaxHeap(bool m) : mode(m) {};
```

在 Max Heap 和 min Heap 兩者差在 Heap 結構的特性，Max Heap 為從上到下遵守父節點大於兩個子節點的規則，而 minHeap 則為相反，從上到下父節點皆小於其兩個子節點因此在程式中僅有 shiftUp 和 shiftDown 兩個負責維護 Heap 結構的函示中有所差異

## 程式實作

```cpp
template <typename T>
void minAndMaxHeap<T>::shiftUp(int index) { // 從 index 節點開始往上浮檢查符合min or Max Heap規則
  while (index > 0) {
    int parentIndex = (index - 1) / 2;
    if ((heap[parentIndex] <= heap[index] && !mode) ||
        heap[parentIndex] >= heap[index] && mode) {
      break;
    }
    std::swap(heap[parentIndex], heap[index]);
    index = parentIndex;
  }
}
```

```cpp
template <typename T>
void minAndMaxHeap<T>::shiftDown(int index) { // 從 index 節點開始往下檢查符合min or Max Heap規則
  while (true) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap.size() &&
        ((heap[left] < heap[smallest] && !mode) || (heap[left] > heap[smallest] && mode))) {
      smallest = left;
    }
    if (right < heap.size() &&
        ((heap[right] < heap[smallest] && !mode) || (heap[right] > heap[smallest] && mode))) {
      smallest = right;
    }

    if (smallest == index)
      break;

    std::swap(heap[index], heap[smallest]);
    index = smallest;
  }
}
```

以上兩個 function 是用於維護 Heap 特性的函式

分別為 上浮 和 下沉，會再有 push 和 pop 時 (對資料操作時) 呼叫

### push 和 pop

push(T) 是在 Heap 的最後一個節點新增，因此要在最後一個節點開始 shiftUp 上浮

Pop() 會把最頂端的節點取出，再拿最後一個節點替換掉空缺，因此使用 shiftDown 下沉

### Sort

有了以上 Heap 的架構，就可以輕鬆的拿來做排序了
以下是使用 minAndMaxHeap 類別 用來排序的簡單範例和結果

```cpp
  const int numElement = 50;
  const int randMax = 100;
  srand((unsigned)time(NULL));
  minAndMaxHeap<int> mh(false); // false 為 min Heap 從小排到大

  std::cout << "Before sort:" << std::endl;
  for (int i = 0; i < 99; i++) {
    int randomNumber = gerenteRandomNumber(randMax);
    mh.push(randomNumber);
    std::cout << randomNumber << " ";
  }

  std::cout << std::endl
            << "After sort:" << std::endl;
  for (int i = 0; i < 99; i++) {
    std::cout << mh.getTop() << " ";
    mh.pop();
  }
```

## 測試與驗證

### minHeap

```Plaintext
Before sort:
34 83 62 48 9 73 27 67 28 20 60 41 35 87 26 82 97 68 94 38 21 26 46 18 94 48 96 74 87 73 29 7 52 81 90 73 40 3 55 9 51 85 77 57 43 27 70 72 67 28 50 68 34 85 52 89 42 100 38 44 86 80 29 79 60 5 36 63 89 58 42 75 38 37 90 11 92 79 51 28 26 29 44 54 89 78 53 16 88 46 11 23 42 62 93 45 5 1 19
After sort:
1 3 5 5 7 9 9 11 11 16 18 19 20 21 23 26 26 26 27 27 28 28 28 29 29 29 34 34 35 36 37 38 38 38 40 41 42 42 42 43 44 44 45 46 46 48 48 50 51 51 52 52 53 54 55 57 58 60 60 62 62 63 67 67 68 68 70 72 73 73 73 74 75 77 78 79 79 80 81 82 83 85 85 86 87 87 88 89 89 89 90 90 92 93 94 94 96 97 100
```

### MaxHeap

```Plaintext
Before sort:
65 35 33 8 76 70 53 80 32 73 44 3 54 80 76 77 72 13 87 20 89 71 47 90 89 15 70 42 89 75 95 8 38 38 97 33 34 63 8 42 46 65 98 13 54 82 47 42 42 94 84 75 66 83 53 54 1 54 45 54 45 13 15 100 70 19 57 71 80 99 39 54 66 81 73 97 36 65 77 48 95 26 25 15 80 42 16 72 10 98 2 73 20 8 61 13 86 99 13
After sort:
100 99 99 98 98 97 97 95 95 94 90 89 89 89 87 86 84 83 82 81 80 80 80 80 77 77 76 76 75 75 73 73 73 72 72 71 71 70 70 70 66 66 65 65 65 63 61 57 54 54 54 54 54 54 53 53 48 47 47 46 45 45 44 42 42 42 42 42 39 38 38 36 35 34 33 33 32 26 25 20 20 19 16 15 15 15 13 13 13 13 13 10 8 8 8 8 3 2 1
```

類別是使用樣板，所以也可以排序別種資料型態

例如 float

```Plaintext
Before sort:
4.96109 3.48552 2.94198 8.464 8.28486 0.477615 1.48625 3.0369 7.64 2.11737
After sort:
8.464 8.28486 7.64 4.96109 3.48552 3.0369 2.94198 2.11737 1.48625 0.477615
```

排序結果都正常

### 編譯與執行命令

編譯

```Bash
g++ -g mainSort.cpp testSort/quickSort.cpp -o ./mainSort.exe
```

執行

```Bash
./mainSort.exe
```

## 效能分析

為了比較我們使用了以下 3 種排序已利比較表現結果

- Quick sort
- STL sort
- heap sort

以下為 3 種排序方法在不同的資料筆數、測試數排序的時間

以下每個測試都包含 IO 時間，每筆 sort 前 sort 後結果都會輸出到 Terminal，但每個輸出的都一樣內容，因此依然可以公正的比較

### 筆數

```Plaintext
排序數列筆數: 10, 隨機數值最大值: 1000, 測試回合:10
Heap sort   Avg: 1.754 ms
STL sort    Avg: 1.893 ms
quick sort  Avg: 1.429 ms
```

▲ 十筆情況差距不大，Quick Sort 微幅領先

```Plaintext
排序數列筆數: 1000, 隨機數值最大值: 1000, 測試回合:10
Heap sort   Avg: 129.043 ms
STL sort    Avg: 148.523 ms
quick sort  Avg: 140.193 ms
```

▲ 一千筆 Heap sort 超車成為最快的排序

```Plaintext
排序數列筆數: 10000, 隨機數值最大值: 1000, 測試回合:10
Heap sort   Avg: 1243.33 ms
STL sort    Avg: 1180.98 ms
quick sort  Avg: 1218.93 ms
```

▲ 一萬筆就變成了 STL sort 最快了，Quick Sort 則比 Heap Sort 快了 30ms，差距極小似乎可以忽略不計

```Plaintext
排序數列筆數: 100000, 隨機數值最大值: 1000, 測試回合:10
Heap sort   Avg: 12166 ms
STL sort    Avg: 11942.9 ms
quick sort  Avg: 12396.2 ms
```

▲ 十萬筆 STL 老樣是最快的，測了好幾次 Quick sort 和 heap sort 兩者不相上下，沒有誰比較快

### 數列分布

```Plaintext
排序數列筆數: 10000, 隨機數值最大值: 100, 測試回合:10
Heap sort   Avg: 1154.36 ms
STL sort    Avg: 1128.88 ms
quick sort  Avg: 1156.6 ms
```

```Plaintext
排序數列筆數: 10000, 隨機數值最大值: 1000, 測試回合:10
Heap sort   Avg: 1206.83 ms
STL sort    Avg: 1185.29 ms
quick sort  Avg: 1178.06 ms
```

```Plaintext
排序數列筆數: 10000, 隨機數值最大值: 10000, 測試回合:10
Heap sort   Avg: 1241.7 ms
STL sort    Avg: 1175.78 ms
quick sort  Avg: 1183.18 ms
```

```Plaintext
排序數列筆數: 10000, 隨機數值最大值: 1000000, 測試回合:10
Heap sort   Avg: 1207.54 ms
STL sort    Avg: 1184.87 ms
quick sort  Avg: 1198.41 ms
```

HeapSort 看起來數列分布對時間的影響度是三者裡最高的

### 圖表

![chart1](./src/images/chart1.png#pic_center=600x600)

### 時間複雜度

1. Push(t)

push 會將推入至最底端，然後再用 Shift up 向上搬移，直到符合 Heap 的要求。Heap 的高度是 $logn$

最佳時間複雜度: o(1)  
最壞時間複雜度: O($logn$)

2. pop()

pop 會將最上方的節點素替換做末端節點，然後再呼叫 shiftDown() 往下沉滿足 Heap 的要求。

時間複雜度: O($logn$)

#### Heap Sort 整體時間複雜度

Heap Sort 將 n 個元素 Push() 到 Heap 中，再依序執行 n 個 pop()

push()將花費 $n logn$

pop()將花費同樣 $n logn$

因此總共需要 $2n logn$

Heap Sort 的整體時間複雜度為 O($n log n$)。

### 空間複雜度

本專案 Heap 是使用 Vector 實作，除此之外並沒有使用額外的動態記憶體分配，Push(), pop(), 空間複雜度為 O(1)

Heap Sort 的整體空間複雜度為: O(n)

## 申論及開發報告

### 為甚麼使用 tpp (template implementation)

由於 C++ 的樣板（template）設計特性，樣板的實作必須在編譯期間就能被看到，這代表所有的樣板程式碼（不論是定義或實作）通常都需要寫在 .hpp 或 .h 檔中。

然而，為了讓介面（宣告）與實作做更清楚的分離，我們將樣板函式的實作獨立寫在 .tpp 檔案中，再由 .hpp 檔以 #include "minAndMax_heap.tpp" 的方式引入。

這樣還可以帶來以下好處

1. 專案結構更清晰

2. 提升可讀性與模組化

### 心得

#### 黃安可心得

#### 黃順駿心得
