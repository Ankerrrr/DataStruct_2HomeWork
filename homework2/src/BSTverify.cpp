#include "BST.hpp"
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>

const int randMax = 100000000;

int generateNumber(int m) {
  return rand() % m + 1;
}

float cacu(int height, int n) {
  return height / (log(n) / log(2));
}

float avg(std::vector<float> v) {
  float ans = 0;
  for (float i : v) {
    ans += i;
  }
  return ans / v.size();
}

float mid(std::vector<float> v) {
  std::sort(v.begin(), v.end());
  int size = v.size();
  if (size % 2 == 1 && size != 1) {
    return (v[size / 2] + v[size / 2 + 1]) / 2.0f;
  } else {
    return v[size / 2];
  }
}

int main() {
  // srand(time(NULL));
  // std::vector<float> vectorScore;

  // int testIndex = 0;
  // int testValue[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 50000, 60000, 70000, 80000, 90000, 100000};
  // int length = sizeof(testValue) / sizeof(testValue[0]);

  // for (; testIndex < length; ++testIndex) {
  //   int i = testValue[testIndex];
  //   BST<int> bst;
  //   for (int j = 0; j < i; j += 1) {
  //     bst.push(generateNumber(randMax));
  //   }
  //   std::cout << "i=" << i << ": ";
  //   float score = cacu(bst.getHeight(), i);
  //   vectorScore.push_back(score);
  //   std::cout << score << std::endl;
  // }
  // std::cout << "Avg: " << avg(vectorScore) << std::endl;
  // std::cout << "Mid: " << mid(vectorScore) << std::endl;

  /* test */
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

  float score = cacu(bst.getHeight(), 12);
  vectorScore.push_back(score);
  std::cout << score << std::endl;
  std::cout << "Avg: " << avg(vectorScore) << std::endl;
  std::cout << "Mid: " << mid(vectorScore) << std::endl;
}
