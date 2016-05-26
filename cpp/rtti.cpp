/*
 * =====================================================================================
 *
 *       Filename:  rtti.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/20/2015 11:08:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <typeinfo>

using namespace std;

class Base {
public:
	virtual void f() {}
};

class Derive : public Base {
public:
	virtual void f() {}
	virtual void f2() { cout << "Derive::f2()" << endl; }
};

class Derive2 : public Base {
public:
	virtual void f2() { cout << "Derive2::f2()" << endl; }
};

void f(Base *pBase)
{
	const type_info &ti = typeid(pBase);
	cout << ti.name() << endl;

	if (dynamic_cast<Derive *>(pBase)) {
		cout << "type: Derive" << endl;
	} else if (dynamic_cast<Derive2 *>(pBase)) {
		cout << "type: Derive2" << endl;
	}

	return;
}

int main()
{
#if 0
	Base *pBase1 = new Derive();
	Derive *pDerive1 = dynamic_cast<Derive *>(pBase1); // down-cast
	pDerive1->f();

	Base *pBase2 = new Base();
	Derive *pDerive2 = dynamic_cast<Derive *>(pBase2); // up-cast
	if (pDerive2) {
		pDerive2->f();
		pDerive2->f2();
	}

	delete pBase1;
	delete pBase2;
#endif
	cout << "Name: " << typeid(Base).name() << endl;

	Base *pBase1 = new Derive();
	f(pBase1);

	Base *pBase2 = new Derive2();
	f(pBase2);

	return 0;
}
