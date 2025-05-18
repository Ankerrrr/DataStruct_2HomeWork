#include "minPQ.hpp"
#include <vector>

template <typename T>
class MinHeap : public MinPQ<T> {
private:
  std::vector<T> heap;
  void shiftUp(int);
  void shiftDown(int);

public:
  MinHeap() {};
  bool isEmpty() const override;
  const T &getTop() const override;
  void push(const T &x) override;
  void pop() override;
};