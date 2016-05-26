/*
 * =====================================================================================
 *
 *       Filename:  vptr3.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/20/2015 08:05:49 PM
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

class CPoint {
public:
	int m_ix;
	int m_iy;
	CPoint(const int p_ix = 0, const int p_iy = 0) : m_ix(p_ix), m_iy(p_iy) {}

	int getX() const { return m_ix; }
	int getY() const { return m_iy; }

	virtual ~CPoint() {}
};

class Base {
public:
	Base() {
		cout << "In Base:" << endl;
		cout << "Virtual ptr = " << (int *)this << endl;
		cout << "Address of VTable = " << (int *)*(int *)this << endl;
//		cout << "1st entry in vtable: " << (int *)*((int *)*(int *)this+0) << endl;
		cout << "1st entry in vtable: " << (int *)this[0][0] << endl;
//		cout << "2nd entry in vtable: " << (int *)*((int *)*(int *)this+1) << endl;
		cout << "2nd entry in vtable: " << (int *)this[0][1] << endl;
		cout << endl;
	}

	virtual void f1() = 0;
	virtual void f2() = 0;
};

class Derive : public Base {
public:
	Derive() {
		cout << "In Derive:" << endl;
		cout << "Virtual ptr = " << (int *)this << endl;
		cout << "Address of VTable = " << (int *)*(int *)this << endl;
//		cout << "1st entry in vtable: " << (int *)*((int *)*(int *)this+0) << endl;
		cout << "1st entry in vtable: " << (int *)this[0][0] << endl;
//		cout << "2nd entry in vtable: " << (int *)*((int *)*(int *)this+1) << endl;
		cout << "2nd entry in vtable: " << (int *)this[0][1] << endl;
		cout << endl;
	}
};

class MostDerive : public Derive {
public:
	MostDerive() {
		cout << "In MostDerive:" << endl;
		cout << "Virtual ptr = " << (int *)this << endl;
		cout << "Address of VTable = " << (int *)*(int *)this << endl;
//		cout << "1st entry in vtable: " << (int *)*((int *)*(int *)this+0) << endl;
		cout << "1st entry in vtable: " << (int *)this[0][0] << endl;
//		cout << "2nd entry in vtable: " << (int *)*((int *)*(int *)this+1) << endl;
		cout << "2nd entry in vtable: " << (int *)this[0][1] << endl;
	}

	virtual void f1() { cout << "MostDerive:f1()" << endl; }
	virtual void f2() { cout << "MostDerive:f2()" << endl; }
};

int main()
{
#if 0
	CPoint obj(5, 10);

	int *ptr = (int *)&obj;

	// *ptr = virtual table pointer
	*(ptr+1) = 100;
	*(ptr+2) = 200;

	cout << "X=" << obj.getX() << endl;
	cout << "Y=" << obj.getY() << endl;
#endif

	MostDerive d;

	return 0;
}
