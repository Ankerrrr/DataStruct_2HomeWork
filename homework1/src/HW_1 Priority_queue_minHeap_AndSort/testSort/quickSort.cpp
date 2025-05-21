#include <vector>
#include <algorithm>
#include "quickSort.hpp"
#include <iostream>;

int partition(std::vector<int> &arr, int lo, int hi) {
  int pivotIndex = (hi + lo) / 2;

  std::swap(arr[pivotIndex], arr[hi]);
  int i = lo - 1;
  for (int j = lo; j < hi; j++) {
    if (arr[j] < arr[hi]) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[hi]);

  return i + 1;
}

void quickSort(std::vector<int> &arr, int lo, int hi) {
  if (lo < hi) {
    int p = partition(arr, lo, hi);
    quickSort(arr, lo, p - 1);
    quickSort(arr, p + 1, hi);
  }
}

void qs(std::vector<int> arr) {

  std::cout << "Before sort:" << std::endl;
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }

  int lo = 0;
  int hi = arr.size() - 1;
  quickSort(arr, lo, hi);

  std::cout << std::endl
            << "After sort:" << std::endl;
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}