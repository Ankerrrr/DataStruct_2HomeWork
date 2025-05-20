#include "minAndMax_heap.tpp"
#include <ctime>
#include <vector>

float gerenteRandomNumber(float n) {
  return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / n));
}

int main() {
  const int numElement = 10;
  const int randMax = 10;
  srand(static_cast<unsigned>(time(NULL)));
  minAndMaxHeap<float> mh(true);

  std::cout << "Before sort:" << std::endl;
  for (int i = 0; i < numElement; i++) {
    float randomNumber = gerenteRandomNumber(randMax);
    mh.push(randomNumber);
    std::cout << randomNumber << " ";
  }

  std::cout << std::endl
            << "After sort:" << std::endl;
  for (int i = 0; i < numElement; i++) {
    std::cout << mh.getTop() << " ";
    mh.pop();
  }
}