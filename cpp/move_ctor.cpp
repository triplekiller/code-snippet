/*
 * ============================================================================
 *
 *       Filename:  move_ctor.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/17/2015 08:16:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * ============================================================================
 */

// http://en.cppreference.com/w/cpp/language/move_constructor

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct A {
	string s;
	A() : s("test") {}
	A(const A& o) : s(o.s) { cout << "move failed\n"; }
	A(A&& o) noexcept : s(move(o.s)) {}
};

A f(A a)
{
	return a;
}

struct B : A {
	string s2;
	int n;
	// implicit move constructor B::(B&&)
	// call A's move constructor
	// call s2's move constructor
	// make a bitwise copy of n
};

struct C : B {
	~C() {} // destructor prevents implicit move ctor C::(C&&)
};

struct D : C {
	D() {}
	~D() {}
	D(D&&) = default; // force a move ctor anyway
};

int main()
{
	cout << "Trying to move A\n";
	A a1 = f(A()); // move constructor from rvalue temporary
	cout << "Before move, a1.s = " << a1.s << endl;
	A a2 = move(a1);
	cout << "After move, a1.s = " << a1.s << endl;
	cout << "After move, a2.s = " << a2.s << endl;

	cout << "Trying to move B\n";
	B b1;
	cout << "Before move, b1.s = " << b1.s << endl;
	B b2 = move(b1); // call implicit move ctor
	cout << "After move, b1.s = " << b1.s << endl;

	cout << "Trying to move C\n";
	C c1;
	C c2 = move(c1); // calls the copy ctor
	cout << "After move, c1.s = " << c1.s << endl;
	cout << "After move, c2.s = " << c2.s << endl;

	cout << "Trying to move D\n";
	D d1;
	D d2 = move(d1);
	cout << "After move, d1.s = " << d1.s << endl;
	cout << "After move, d2.s = " << d2.s << endl;

	return 0;
}
