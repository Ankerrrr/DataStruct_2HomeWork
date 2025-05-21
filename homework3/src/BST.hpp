#ifndef BST_HPP
#define BST_HPP

template <typename T>
class BST {
public:
  virtual ~BST() {};
  virtual T getTop() const;
  virtual bool isEmpty() const;
  virtual void push(const T);
  virtual void pop();
};

#endif
