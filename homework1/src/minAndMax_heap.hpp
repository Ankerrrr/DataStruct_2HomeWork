#ifndef MINANDMAX_HPP
#define MINANDMAX_HPP

#include "minPQ.hpp"
#include <vector>

template <typename T>
class minAndMaxHeap : public MinPQ<T> {
private:
  bool mode;
  std::vector<T> heap;
  void shiftUp(int);
  void shiftDown(int);

public:
  minAndMaxHeap(bool m) : mode(m) {};
  bool isEmpty() const override;
  const T &getTop() const override;
  void push(const T &x) override;
  void pop() override;
};

#include "./minAndMax_heap.tpp"

#endif