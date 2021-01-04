#include <iostream>
#include <type_traits>

// https://zh.cppreference.com/w/cpp/language/sfinae
// https://jguegant.github.io/blogs/tech/sfinae-introduction.html

// SFINAE = Substitution Failure Is Not An Error

// two ways to use std::enable_if

/*
 *
template <bool, typename T=void>
struct enable_if {
};

template <typename T>
struct enable_if<true, T> {
  using type = T;
}
*
*/

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type is_odd(T i) {
  return bool(i % 2);
}

template <typename T, typename =
  typename std::enable_if<std::is_integral<T>::value>::type> bool is_even(T i) {
  return !bool(i % 2);
}

int main() {
  int i = 1;

  std::cout << std::boolalpha;
  std::cout << "i is odd: " << is_odd(i) << std::endl;
  std::cout << "i is even: " << is_even(i) << std::endl;

  return 0;
}
