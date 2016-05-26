/*
 * =====================================================================================
 *
 *       Filename:  vtable.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/12/2015 08:34:49 AM
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

class Base
{
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
};

class NullClass {

};

int main()
{
	typedef void (*func)(void);
	Base b;
	func ptr = NULL;

	int *funcPtr = (int *)(&b);

	cout << "vtable addr: " << funcPtr << endl;
	cout << "the first func addr: " << (int *)(*funcPtr) << endl;

	ptr = (func)*((int *)(*funcPtr));
	ptr();

	NullClass nc;
	cout << "Empty objetc size is " << sizeof(NullClass) << endl;;

	return 0;
}
