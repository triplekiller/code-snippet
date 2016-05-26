/*
 * =====================================================================================
 *
 *       Filename:  singleton.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/08/2015 04:21:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

// http://xavierzhu.com/?p=139

#include <iostream>

using namespace std;

// singleton class can not be created in stack
class Singleton {
public:
	static Singleton *getInstance();
	void method();
	~Singleton() {}

protected:
	Singleton() {} // protected to be derived

private:
	static Singleton *m_instance;
};

Singleton *Singleton::m_instance = 0;

Singleton *Singleton::getInstance()
{
	if (m_instance == 0) {
		m_instance = new Singleton();
	}

	return m_instance;
}

void Singleton::method()
{
	cout << this << ": " << "method of the singleton class" << endl;
}

// can not be created in heap
// overload operator new() and operator delete()
class A {
public:
	A() { cout << "class only exist in stack" << endl; }
	~A() {}
private:
	void *operator new(size_t n) {}
	void operator delete(void *ptr) {}
};

// can not be created in stack
class B {
public:
	static B *create() { return new B(); }
	void *destroy() { delete this; }

protected:
	B() { cout << "class only exist in heap" << endl; }
	~B() {}
};

int main()
{
	cout << "Singleton test case" << endl;
	Singleton *s1, *s2;
	s1 = Singleton::getInstance();
	s1->method();
	s2 = Singleton::getInstance();
	s2->method();

	A a;
//	A *aPtr = new A();

//	B b;
	B *bPtr = B::create();

	return 0;
}
