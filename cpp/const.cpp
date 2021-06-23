/*
 * =====================================================================================
 *
 *       Filename:  const.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/22/2015 08:56:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>

#include <stdlib.h>

using namespace std;

#define PI 3.14

const double pi = 3.14;

// They serve different purposes. constexpr is mainly for optimization while
// const is for practically const objects like the value of Pi.

// const & constexpr both can be applied to member methods. Member methods are
// made const to make sure that there are no accidental changes by the method.
// On the other hand, the idea of using constexpr is to compute expressions at
// compile time so that time can be saved when the code is running.

// const can only be used with non-static member function whereas constexpr can
// be used with member and non-member functions, even with constructors but with
// condition that argument and return type must be of literal types.

// Where you need a value not often & calculating it would be a bit complex,
// then that is the place you need constexpr. Otherwise, things are fine with an
// older buddy const. For example, Fibonacci number, factorial, etc.

// Often programmer would suggest using constexpr instead of a macro.

int getRandomNum() {
  return rand() % 10;
}

int main() {
  double i = PI;
  double j = PI;
  double k = pi;
  double m = pi;

  cout << &i << endl;
  cout << &j << endl;
  cout << &k << endl;
  cout << &m << endl;

  std::cout << std::endl;

  const int num = getRandomNum();  // OK
  std::cout << "random num: " << num << std::endl;

  // constexpr will always accept a strictly compile-time value.
  // constexpr specifies that the value of an object, variable and a function
  // can be evaluated strictly at compile-time.

  // constexpr int num2 = getRandomNum();  // not OK! compilation error

  return 0;
}
