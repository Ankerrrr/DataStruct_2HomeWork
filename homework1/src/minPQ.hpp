template <typename T>
class MinPQ {
public:
  virtual ~MinPQ() {};
  virtual bool isEmpty() const = 0;
  virtual const T &getTop() const = 0;
  virtual void push(const T &) = 0;
  virtual void pop() = 0;
};