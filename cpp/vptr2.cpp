/*
 * =====================================================================================
 *
 *       Filename:  vptr2.cpp
 *
 *    Description:  memory model test for C++
 *
 *        Version:  1.0
 *        Created:  08/14/2015 07:23:33 PM
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

class Parent {
public:
	int mParentID;

	Parent() : mParentID(10) {}

	virtual void f() { cout << "Parent::f()" << endl; }
	virtual void g() { cout << "Parent::g()" << endl; }
	virtual void h() { cout << "Parent::h()" << endl; }
};

class Child : public Parent {
public:
	int mChildID;

	Child() : mChildID(100) {}

	virtual void f() { cout << "Child::f()" << endl; }
	virtual void g_child() { cout << "Child::g_child()" << endl; }
	virtual void h_child() { cout << "Child::h_child()" << endl; }
};

class GrandChild : public Child {
public:
	int mGrandChildID;

	GrandChild() : mGrandChildID(1000) {}

	virtual void f() { cout << "GrandChild::f()" << endl; }
	virtual void g_child() { cout << "GrandChild::g_child()" << endl; }
	virtual void h_grandchild() { cout << "GrandChild::h_grandchild()" << endl; }
};

typedef void (*func)(void);

int main()
{
	GrandChild gc;
	int **vptr = (int **)&gc;
	func pFunc = NULL;

	cout << "[0] GrandChild::_vptr->" << endl;

	for (int i = 0; (func)vptr[0][i] != NULL; ++i) {
		pFunc = (func)vptr[0][i];	
		cout << "  [" << i << "] ";
		pFunc();
	}

	cout << "[1] Parent.mParentID=" << (int)vptr[1] << endl;
	cout << "[2] Child.mChildID=" << (int)vptr[2] << endl;
	cout << "[1] GrandChild.mGrandChildID=" << (int)vptr[3] << endl;

	return 0;
}
