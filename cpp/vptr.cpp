/*
 * =====================================================================================
 *
 *       Filename:  vptr.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/12/2015 09:38:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

class Base1
{
public:
	virtual void f() { cout << "Base1::f" << endl; }
	virtual void g() { cout << "Base1::g" << endl; }
	virtual void h() { cout << "Base1::h" << endl; }
};

class Base2
{
public:
	virtual void f() { cout << "Base2::f" << endl; }
	virtual void g() { cout << "Base2::g" << endl; }
	virtual void h() { cout << "Base2::h" << endl; }
};

class Base3
{
public:
	virtual void f() { cout << "Base3::f" << endl; }
	virtual void g() { cout << "Base3::g" << endl; }
	virtual void h() { cout << "Base3::h" << endl; }
};

class Derived : public Base1, public Base2, public Base3 {
public:
	virtual void f() { cout << "Derive::f" << endl; }
	virtual void g1() { cout << "Derive::g1" << endl; }
};

typedef void (*func)(void);

int main()
{
	func pfun = NULL;
	Derived d;
	int **vptr = (int **)&d;

	// Base1 vtable
	pfun = (func)vptr[0][0];
	pfun();

	pfun = (func)vptr[0][1];
	pfun();

	pfun = (func)vptr[0][2];
	pfun();

	// Derived vtable
	pfun = (func)vptr[0][3];
	pfun();

	// The tail of the vtable
	pfun = (func)vptr[0][4];
	cout << pfun << endl;

	// Base2 vtable
	pfun = (func)vptr[1][0];
	pfun();

	pfun = (func)vptr[1][1];
	pfun();

	pfun = (func)vptr[1][2];
	pfun();

	// The tail of the vtable
	pfun = (func)vptr[1][3];
	cout << pfun << endl;

	// Base3 vtable
	pfun = (func)vptr[2][0];
	pfun();

	pfun = (func)vptr[2][1];
	pfun();

	pfun = (func)vptr[2][2];
	pfun();

	// The tail of the vtable
	pfun = (func)vptr[2][3];
	cout << pfun << endl;

	return 0;
}
