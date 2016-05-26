/*
 * =====================================================================================
 *
 *       Filename:  nrvo.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/18/2015 10:54:20 AM
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

class Test {
public:
	Test() { cout << "ctor\t" << this << endl; }
	Test(const Test &t) {
		cout << "copy ctor\t" << this << "\tfrom\t" << &t << endl;
	}

	Test& operator=(const Test&) {
		cout << "assignment function\t" << this << endl;
	}

	~Test() { cout << "destructor\t" << this << endl; }
};

// RVO = Return Value Optimization
// NRVO = Named Return Value Optimization
// -fno-elide-constructors disable RVO and force g++ call copy ctor 
Test fRVO()
{
	return Test();
}

Test fNRVO()
{
	cout << "fNRVO begin" << endl;
	Test t;
	cout << "fNRVO end" << endl;

	return t;
}

int main(void)
{
	Test a = Test();	
	cout << "a=" << &a << endl;

	cout << "+++++++++++++++++++++++++" << endl;
	Test b = fRVO();
	cout << "b=" << &b << endl;

	cout << "+++++++++++++++++++++++++" << endl;
	Test c = fNRVO();
	cout << "c=" << &c << endl;

	return 0;
}
