/*
 * =====================================================================================
 *
 *       Filename:  template.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/22/2015 05:20:20 PM
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

template <typename T>
inline const T &max(const T &a, const T &b)
{
	static int i = 0;
	cout << "i++ = " << i++ << endl;

	return a > b ? a : b;
}

class MyClass {
public:
	MyClass(int value) : _value(value) {}

	bool operator> (const MyClass &other) {
		return _value > other._value;
	}

	int getValue() { return _value; }

private:
	int _value;
};

template <typename T>
class Singleton {
public:
	static T *getInstance();

private:
	static T *_instance;
};

template <typename T>
T *Singleton<T>::_instance = NULL;

template <typename T>
T *Singleton<T>::getInstance()
{
	if (_instance == NULL)
		_instance = new T;

	return _instance;
}

class MySingleton : public Singleton<MySingleton> {
public:
	MySingleton() {}
	~MySingleton() {}

	void print() { cout << "MySingleton" << endl; }
};

template <typename T>
class InnerClass {
public:
	static void doTest() { cout << "InnerClass::doTest()" << endl; }
};

template <typename T>
class OuterClass {
public:
	template <typename T2>
	void func() { T2::doTest(); }
};

template <typename T>
void doTest(OuterClass<T> &out)
{
	out.template func< InnerClass<T> >();
}

template <typename T>
int hash_code(T v)
{
	return v.hashCode() * 2;
}

template <typename T>
int hash_code(T *v)
{
	return v->hashCode();
}

int hash_code(const int v)
{
	return v + 100;
}

class HashClass {
public:
	HashClass(int v) : _v(v) {}
	int hashCode() { return _v + 200; }

private:
	int _v;
};

template<typename T>
T remainder(T a, T b)
{
	if (a - b >= b) {
		a = remainder(a, b + b);
		if (a < b)
			return a;
	}

	return a - b;
}

int main()
{
	int cnt = 0;

	cout << endl << "########## case " << ++cnt << endl;
	::max(4, 5);
	::max(5, 6);
	::max(5.3, 5.6);
	::max(5.3, 5.6);

	MyClass m1(30), m2(40);
	::max(&m1, &m2);

	cout << endl << "########## case " << ++cnt << endl;
	MySingleton *obj = MySingleton::getInstance();
	obj->print();

	cout << endl << "########## case " << ++cnt << endl;
	OuterClass<int> out;
	doTest(out);

	// template function overload
	cout << endl << "########## case " << ++cnt << endl;
	HashClass c1(10);
	cout << "hash value = " << hash_code(c1) << endl;

	HashClass c2(20);
	cout << "hash value = " << hash_code(&c2) << endl;

	int val = 30;
	cout << "hash value = " << hash_code(val) << endl;

	cout << endl << "########## case " << ++cnt << endl;
	int a = 100, b = 13;
	cout << "remainder(a, b)=" << remainder(a, b) << endl;

	return 0;
}
