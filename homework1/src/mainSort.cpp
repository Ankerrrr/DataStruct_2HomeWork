#include "minAndMax_heap.hpp"
#include <ctime>
#include <vector>
#include <chrono>
#include <algorithm>
#include "testSort/quickSort.hpp"

const int numElement = 10000;
const int randMax = 1000000;
const int round = 10;

minAndMaxHeap<int> mh(false);
std::vector<int> data;

float avgVector(std::vector<float> a) {
  float avg;
  for (float i : a) {
    avg += i;
  }
  return avg / a.size();
}

float gerenteFloatRandomNumber(float n) {
  return static_cast<int>(rand()) / (static_cast<float>(RAND_MAX / n));
}

void gerenteIntRandomNumberToVector() {
  for (int i = 0; i < numElement; i++) {
    data.push_back(rand() % randMax + 1);
  }
}

void sortHeap(std::vector<int> data) {
  std::cout << "Before sort:" << std::endl;
  for (int i = 0; i < numElement; i++) {
    mh.push(data[i]);
    std::cout << data[i] << " ";
  }

  std::cout << std::endl
            << "After sort:" << std::endl;
  for (int i = 0; i < numElement; i++) {
    std::cout << mh.getTop() << " ";
    mh.pop();
  }
  std::
          cout
      << std::endl;
}

void STLsort(std::vector<int> data) {
  std::cout << "Before sort:" << std::endl;
  for (int i = 0; i < numElement; i++) {
    std::cout << data[i] << " ";
  }

  std::sort(data.begin(), data.end());

  std::cout << std::endl
            << "After sort:" << std::endl;
  for (int i = 0; i < data.size(); i++) {
    std::cout << data[i] << " ";
  }
  std::
          cout
      << std::endl;
}

double recordTime(void (*func)(std::vector<int>), std::vector<int> data) {
  auto start = std::chrono::high_resolution_clock::now();
  func(data);
  auto end = std::chrono::high_resolution_clock::now();

  double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
  return duration;
}

int main() {
  srand(static_cast<unsigned>(time(NULL)));
  std::vector<float> recordHeapTime;
  std::vector<float> recordSTLTime;
  std::vector<float> recordQuickTime;

  for (int i = 0; i < 1; i++) { // 暗碭
    gerenteIntRandomNumberToVector();
    recordHeapTime.push_back(recordTime(sortHeap, data));
    recordSTLTime.push_back(recordTime(STLsort, data));
    recordQuickTime.push_back(recordTime(qs, data));
  }

  std::cout << "逼计掸计: " << numElement << ", 繦诀计程: " << randMax << ", 代刚:" << round << std::endl;
  std::cout << "Heap sort " << "  Avg: " << avgVector(recordHeapTime) << " ms" << std::endl;
  std::cout << "STL sort " << "   Avg: " << avgVector(recordSTLTime) << " ms" << std::endl;
  std::cout << "quick sort " << " Avg: " << avgVector(recordQuickTime) << " ms" << std::endl;
}