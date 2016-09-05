/*
 * ============================================================================
 *
 *       Filename:  vector.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/21/2015 10:05:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * ============================================================================
 */

// vector/string: has capacity attribute
// list/map/multimap/set/multiset: no capacity attribute

// Capacity is the amount of space that the vector is currently using.
// Under the hood, a vector just uses an array. The capacity of the vector is
// the size of the array. This is always equal or larger than the size.
// You should almost never care about the capacity.

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef vector<int> INTVEC;

class Sample {
public:
	Sample() { cout << "Default ctor" << endl; }
	Sample (const Sample &obj) {
		cout << "Sample copy ctor" << endl;
	}
};

int main()
{
	const char *str = "hello world";
	int a[5] = {1, 3, 5, 7, 9};
	vector<char> v(str, str + strlen(str));
	vector<int> v2(a, a + sizeof(a)/sizeof(a[0]));

	vector<char>::iterator iter;
	vector<int>::iterator iter2;

	cout << "print v:" << endl;
	for (iter = v.begin(); iter != v.end(); iter++)
		cout << *iter << endl;

	cout << "print v2:" << endl;
	for (iter2 = v2.begin(); iter2 != v2.end(); iter2++)
		cout << *iter2 << endl;

	cout << endl << "########" << endl;

	INTVEC vec;
	vec.push_back(42);

	// size: number of elements in the vector
	// max_size: maximum number of elements vector can hold(implementation dependent)
	// capacity: number of elements for which memory has been allocated
	// resize: reallocate memory for the vector, preserve contents if new size
	//		is larger than existing size
	// reserve: allocate elements for vector to ensure a minimum size, preserving
	//		its contents if the new size is larger then existing size
	// push_back: append/insert an element to the end of a vector, allocating
	//		memory for it if necessary
	cout << "vec.size()=" << vec.size() << endl;
	cout << "vec.max_size()=" << vec.max_size() << endl;
	cout << "vec.capacity()=" << vec.capacity() << endl;

	vec.reserve(1000);
	cout << endl << "After reserving storage for 1000 elements:" << endl;
	cout << "vec.size()=" << vec.size() << endl;
	cout << "vec.max_size()=" << vec.max_size() << endl;
	cout << "vec.capacity()=" << vec.capacity() << endl;

	vec.resize(2000);
	cout << endl << "After resizing storage for 2000 elements:" << endl;
	cout << "vec.size()=" << vec.size() << endl;
	cout << "vec.max_size()=" << vec.max_size() << endl;
	cout << "vec.capacity()=" << vec.capacity() << endl;

	cout << endl << "########" << endl;
	INTVEC myVec;
	for (int i = 0; i < 10; ++i)
		myVec.push_back(i);
	cout << "after mvVec push_back:" << endl;
	cout << "myVec.size()=" << myVec.size() << endl;
	cout << "myVec.capacity()=" << myVec.capacity() << endl;

//	void resize (size_type n);
//	void resize (size_type n, const value_type& val);
// if n > capacity, an auto reallocation happens
	myVec.resize(5);
	cout << "after resize(5):" << endl;
	cout << "myVec.size()=" << myVec.size() << endl;
	cout << "myVec.capacity()=" << myVec.capacity() << endl;

	myVec.resize(8, 100);
	cout << "after resize(8, 100):" << endl;
	cout << "myVec.size()=" << myVec.size() << endl;
	cout << "myVec.capacity()=" << myVec.capacity() << endl;

	myVec.resize(12);
	cout << "after resize(12)" << endl;
	cout << "myVec.size()=" << myVec.size() << endl;
	cout << "myVec.capacity()=" << myVec.capacity() << endl;
	cout << "myVec contains:" << endl;
	for (int i = 0; i < myVec.size(); ++i)
		cout << myVec[i] << ' ';
	cout << endl;

	cout << endl << "########" << endl;
	INTVEC::size_type sz;
	INTVEC foo;
	sz = foo.capacity();
	cout << "default capacity for vector<int>: " << (int)sz << endl;
	for (int i = 0; i < 100; ++i) {
		foo.push_back(i);
		if (sz != foo.capacity()) {
			sz = foo.capacity();
			cout << "capacity changed: " << sz << endl;
		}
	}

	INTVEC bar;
	bar.reserve(50);
	sz = bar.capacity();
	cout << "first reserve 50 for vector, capacity is " << sz << endl;
	for (int i = 0; i < 100; ++i) {
		bar.push_back(i);
		if (sz != bar.capacity()) {
			sz = bar.capacity();
			cout << "capacity changed: " << sz << endl;
		}
	}

	cout << endl << "########" << endl;
	vector<Sample> samVec;
	cout << "Capacity: " << samVec.capacity() << endl;
	cout << "Size: " << samVec.size() << endl;

	// ctor of Sample will be called
	Sample so;
	samVec.push_back(so);
	cout << "Capacity: " << samVec.capacity() << endl;
	cout << "Size: " << samVec.size() << endl;

	samVec.push_back(Sample());
	cout << "Capacity: " << samVec.capacity() << endl;
	cout << "Size: " << samVec.size() << endl;

	cout << endl << "########" << endl;
	vector<int> ve;
	ve.push_back(11);
	ve.push_back(22);
	ve.push_back(33);
	ve.push_back(44);
	ve.push_back(55);

	for (auto &i : ve) {
		cout << i << endl;
	}

	cout << "ve.size()=" << ve.size() << endl;

	ve.erase(remove_if(ve.begin(), ve.end(),
		[](int e) { return e % 2 == 1; }), ve.end());

	for (auto &i : ve) {
		cout << i << endl;
	}

	cout << "ve.size()=" << ve.size() << endl;

	return 0;
}
