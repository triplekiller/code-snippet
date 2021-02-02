#include <iostream>
#include <memory>

// C++11 lets us perform perfect forwarding, which means that we can forward the
// parameters passed to a function template to another function call inside it
// without losing their own qualifiers (const-ref, ref, value, rvalue, etc.).

struct A {
  A(int&& n) {
    std::cout << "rvalue overload, n=" << n << std::endl;
  }

  A(int& n) {
    std::cout << "lvalue overload, n=" << n << std::endl;
  }
};

class B {
 public:
  template <typename T1, typename T2, typename T3>
  B(T1&& t1, T2&& t2, T3&& t3)
      : a1_(std::forward<T1>(t1)),
        a2_(std::forward<T2>(t2)),
        a3_(std::forward<T3>(t3)) {}

 private:
  A a1_, a2_, a3_;
};

template <typename T, typename U>
std::unique_ptr<T> make_unique(U&& u) {
  return std::unique_ptr<T>(new T(std::move(u)));
}

template <typename T, typename... U>
std::unique_ptr<T> make_unique2(U&&... u) {
  return std::unique_ptr<T>(new T(std::move(u)...));
}

int main(int argc, char** argv) {
  auto p1 = make_unique<A>(2);

  int i = 10;
  auto p2 = make_unique<A>(i);

  int j = 100;
  auto p3 = make_unique2<B>(i, 2, j);

  return 0;
}
