/*
 * =====================================================================================
 *
 *       Filename:  smart_ptr.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/31/2015 04:33:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <memory>

using namespace std;

class foo
{
public:
	void print() { cout << "foo:print" << endl; }
};

void func(int *p)
{
	cout << "*p=" << *p << endl;
}

int main()
{
	cout << "####for deprecated auto_ptr in C++" << endl;
	auto_ptr<foo> ap1(new foo);
	ap1->print();
	cout << "ap1 ptr: " << ap1.get() << endl;

	auto_ptr<foo> ap2(ap1);
	ap2->print();
	cout << "ap1 ptr: " << ap1.get() << endl;
	cout << "ap2 ptr: " << ap2.get() << endl;

	cout << endl;
	cout << "####for shared_ptr..." << endl;
	shared_ptr<foo> sp1(new foo);
	sp1->print();
	cout << "sp1 ptr: " << sp1.get() << endl;
	shared_ptr<foo> sp2(sp1);
	sp2->print();
	cout << "sp2 ptr: " << sp2.get() << endl;

	// unique_ptr: copy ctor not exist but move ctor exist
	cout << endl;
	cout << "####for unique_ptr..." << endl;
	unique_ptr<int> p1(new int(40));
	unique_ptr<int> p2 = move(p1); // transfer ownership

	// p1 is nullptr
	if (p1)
		func(p1.get());

	(*p2)++;

	if (p2)
		func(p2.get());

/*
make_shared<T> is a non-member function and has the advantage of allocating
memory for the shared object and the smart pointer with a single allocation,
as opposed to the explicit construction of a shared_ptr via the contructor,
that requires at least two allocations. In addition to possible overhead, there
can be situations where memory leaks can occur because of that
*/

// std::weak_ptr is a smart pointer that holds a non-owning ("weak")
// reference to an object that is managed by std::shared_ptr. It must be
// converted to std::shared_ptr in order to access the referenced object

	cout << endl;
	cout << "###for weak_ptr..." << endl;
	auto p = make_shared<int>(45);
	weak_ptr<int> wp = p;

	auto sp = wp.lock(); // create a shared_ptr that manages the referenced object
	cout << *sp << endl;

	p.reset(); // release the ownership of the managed object
	if (wp.expired()) // check whether the referenced object was already deleted
		cout << "expired" << endl;

	return 0;
}
