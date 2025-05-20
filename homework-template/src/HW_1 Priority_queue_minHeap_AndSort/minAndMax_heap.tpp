#include "./minAndMax_heap.hpp"
#include <iostream>
#include <algorithm>

template <typename T>
bool minAndMaxHeap<T>::isEmpty() const {
  if (heap.size() != 0) {
    return false;
  }
  return true;
}

template <typename T>
const T &minAndMaxHeap<T>::getTop() const {
  if (heap.size() == 0) {
    throw "nothing can GET in heap";
  }
  return heap[0];
}

template <typename T>
void minAndMaxHeap<T>::push(const T &x) {
  heap.push_back(x);
  shiftUp(heap.size() - 1);
}

template <typename T>
void minAndMaxHeap<T>::pop() {
  if (isEmpty()) {
    throw "isEmpty cant Pop";
  }
  heap[0] = heap.back();
  heap.pop_back();
  if (!isEmpty()) {
    shiftDown(0);
  }
}

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