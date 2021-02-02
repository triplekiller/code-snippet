#include <functional>
#include <iostream>
#include <utility>

using namespace std;

enum IntType { TYPE_1, TYPE_2 };

void func(int& n1, int& n2, const int& n3) {
  std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  ++n1;  // increments the copy of n1 stored in the function object
  ++n2;  // increments the main()'s n2
         // ++n3; // compile error
}

void test_ref() {
  int n1 = 1, n2 = 2, n3 = 3;

  std::function<void()> bound_f =
      std::bind(func, n1, std::ref(n2), std::cref(n3));

  n1 = 10;
  n2 = 11;
  n3 = 12;

  std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  bound_f();
  std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
}

int main() {
  std::pair<int, IntType> pa1, pa2;
  pa1 = make_pair(1, TYPE_2);
  pa2 = make_pair(1, TYPE_2);

  if (pa1 == pa2)
    cout << "equal" << endl;
  else
    cout << "not equal" << endl;

  int n = 1;
  int a[5] = {1, 2, 3, 4, 5};

  // build a pair from two ints
  auto p1 = std::make_pair(n, a[1]);
  std::cout << "The value of p1 is "
            << "(" << p1.first << ", " << p1.second << ")\n";

  // build a pair from a reference to int and an array (decayed to pointer)
  auto p2 = std::make_pair(std::ref(n), a);
  n = 7;
  std::cout << "The value of p2 is "
            << "(" << p2.first << ", " << *(p2.second + 2) << ")\n";

  std::cout << std::endl;

  test_ref();

  return 0;
}
