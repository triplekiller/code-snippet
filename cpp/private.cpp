/*
 * =====================================================================================
 *
 *       Filename:  private.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/13/2015 01:48:12 PM
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

class A {
public:
	A() : i(10) {}
	void print() { cout << "A::i=" << i << endl; }

private:
	const int i;
};

int main()
{
	A a;

	a.print();
	int *p = (int *)&a;

	*p = 30;
	a.print();

	// g++ -Dprivate=public private.cpp
	cout << a.i << endl;
}
