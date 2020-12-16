#include <iostream>
#include <memory>
#include <vector>
#include <chrono>

// g++ -std=c++11 smart_ptr.cpp

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

void move_shared_ptr() {
	std::vector<std::shared_ptr<int> > v(10000, std::shared_ptr<int>(new int(3)));
	typedef std::chrono::high_resolution_clock Clock;
	typedef Clock::time_point time_point;
	typedef std::chrono::duration<double, std::micro> us;
	time_point t0 = Clock::now();
	v.erase(v.begin());
	time_point t1 = Clock::now();
	std::cout << us(t1-t0).count() << "\u00B5s\n";
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
	cout << "sp1 use_count: " << sp1.use_count() << '\n';
	shared_ptr<foo> sp2(sp1);
	sp2->print();
	cout << "sp2 ptr: " << sp2.get() << endl;
	cout << "sp1 use_count: " << sp1.use_count() << '\n';
//	cout << "sp2 use_count: " << sp2.use_count() << end;
	cout << "sp2 use_count: " << sp2.use_count() << '\n';

	/*
	A std::unique_ptr can't be passed by value because it can't be copied, so it
	is usually moved around with the special function std::move from the
	Standard Library

	Go with a simpler raw pointer (can be null) or a reference (can't be null)
	when your function just needs to inspect the underlying object or do
	something with it without messing with the smart pointer. Both
	std::unique_ptr and std::shared_ptr have the get() member function that
	returns the stored pointer
	*/

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

	cout << endl;
	move_shared_ptr();

	return 0;
}
