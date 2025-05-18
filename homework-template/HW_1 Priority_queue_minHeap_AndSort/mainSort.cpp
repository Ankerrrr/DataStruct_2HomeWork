#include "minheap.tpp"
#include <time.h>
#include <vector>

int gerenteRandomNumber(int n) {
  return rand() % n + 1;
}

int main() {
  const int numElement = 50;
  const int randMax = 100;
  srand((unsigned)time(NULL));
  MinHeap<int> mh;

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
}