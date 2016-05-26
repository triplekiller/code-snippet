/*
 * =====================================================================================
 *
 *       Filename:  new.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/12/2015 09:25:17 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

// raw operator new acts as a raw memory allocator similar to malloc
// operator new can be overloaded: memory allocation + object construction
// improve performance, debugging/statistics, customization

// placement new: skip memory allocation, construct an object on memory that's already allocated
// custom non-intrusive memory mangement: do not need to change the class itself(mempool)
// allocate memory in special regions: shared memory and mmaped IO
// many container libraries preallocate large buffers of memory

#include <iostream>
#include <vector>

class Base {
public:
	void *operator new(size_t sz) {
		std::cout << "new " << sz << " bytes" << std::endl;
		// if use "return new(sz)", recursion happens
		return ::operator new(sz);
	}

	void operator delete(void *p) {
		std::cout << "overloaded delete" << std::endl;
		::operator delete(p);
	}

private:
	int m_data;
};

class Derived : public Base {
private:
	int m_derived_data;
	std::vector<int> x, y, z, w;
};

int main()
{
	std::cout << "#### test case for operator new:" << std::endl;

	std::cout << "sizeof(vector<int>)=" << sizeof(std::vector<int>) << std::endl;
	std::cout << "sizeof(Base)=" << sizeof(Base) << std::endl;
	std::cout << "sizeof(Derived)=" << sizeof(Derived) << std::endl;

	// will call this->new other than the globally ::operator new
	Base *p = new Base;
	delete p;

	Derived *d = new Derived;
	delete d;

	std::cout << "#### test case for placement new:" << std::endl;

	int *ptr = new int;
	std::cout << "ptr=" << ptr << std::endl;

	char mem[sizeof(int)];
	std::cout << "mem=" << (void *)mem << std::endl;
	int *ptr2 = new(mem) int;
	std::cout << "ptr2=" << ptr2 << std::endl;

	// no need to call delete ptr2, will cause SEGEV
	// can manually call destructor: fooPtr->~Foo();

	return 0;
}
