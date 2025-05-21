# 41243243 41243244

## 黃安可 黃順駿

第二次作業

含 1, 2, 3 題 報告

## Max / min Heap 作業 2_1

### 解題說明

本題要求實作一個最小優先佇列（Min Priority Queue）的資料結構，並實作出最小堆積樹(min Heap)和最大堆積樹(Max Heap)。為了驗證 minHeap 的功能是否正確，我們將使用該堆積樹進行排序，並透過排序後的結果來檢驗其正確性

### 解題策略

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

如以下程式

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

### minHeap

```
Before sort:
34 83 62 48 9 73 27 67 28 20 60 41 35 87 26 82 97 68 94 38 21 26 46 18 94 48 96 74 87 73 29 7 52 81 90 73 40 3 55 9 51 85 77 57 43 27 70 72 67 28 50 68 34 85 52 89 42 100 38 44 86 80 29 79 60 5 36 63 89 58 42 75 38 37 90 11 92 79 51 28 26 29 44 54 89 78 53 16 88 46 11 23 42 62 93 45 5 1 19
After sort:
1 3 5 5 7 9 9 11 11 16 18 19 20 21 23 26 26 26 27 27 28 28 28 29 29 29 34 34 35 36 37 38 38 38 40 41 42 42 42 43 44 44 45 46 46 48 48 50 51 51 52 52 53 54 55 57 58 60 60 62 62 63 67 67 68 68 70 72 73 73 73 74 75 77 78 79 79 80 81 82 83 85 85 86 87 87 88 89 89 89 90 90 92 93 94 94 96 97 100
```

### MaxHeap

```
Before sort:
65 35 33 8 76 70 53 80 32 73 44 3 54 80 76 77 72 13 87 20 89 71 47 90 89 15 70 42 89 75 95 8 38 38 97 33 34 63 8 42 46 65 98 13 54 82 47 42 42 94 84 75 66 83 53 54 1 54 45 54 45 13 15 100 70 19 57 71 80 99 39 54 66 81 73 97 36 65 77 48 95 26 25 15 80 42 16 72 10 98 2 73 20 8 61 13 86 99 13
After sort:
100 99 99 98 98 97 97 95 95 94 90 89 89 89 87 86 84 83 82 81 80 80 80 80 77 77 76 76 75 75 73 73 73 72 72 71 71 70 70 70 66 66 65 65 65 63 61 57 54 54 54 54 54 54 53 53 48 47 47 46 45 45 44 42 42 42 42 42 39 38 38 36 35 34 33 33 32 26 25 20 20 19 16 15 15 15 13 13 13 13 13 10 8 8 8 8 3 2 1
```

類別是使用樣板，所以也可以排序別種資料型態

例如 float

```
Before sort:
4.96109 3.48552 2.94198 8.464 8.28486 0.477615 1.48625 3.0369 7.64 2.11737
After sort:
8.464 8.28486 7.64 4.96109 3.48552 3.0369 2.94198 2.11737 1.48625 0.477615
```

## 其他

### tpp

因為樣板一定要寫在 hpp 裡面，為了要讓實作和定義分離，因此我們把 minAndMax 的類別實作寫在 **.tpp**內，叫 tpp 是因為他是 template 的實作程式。
