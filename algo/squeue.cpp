/*
 * =====================================================================================
 *
 *       Filename:  squeue.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/08/2015 10:22:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <stack>

using namespace std;

template<typename T>
class SQueue
{
public:
	SQueue() {}
	~SQueue() {}

	void enqueue(const T &x);
	T dequeue();

private:
	stack<T> s1, s2;
};

template<typename T>
void SQueue<T>::enqueue(const T &x)
{
	s1.push(x);
}

// in C, "void fun(void);" means no arguments
// in C, "void fun();" means any arguments
// in C++, "void fun();" and "void fun(void)" means no arguments
template<typename T>
T SQueue<T>::dequeue()
{
	T top;
	if (!s2.empty()) {
		top = s2.top();
		s2.pop();
		return top;
	}

	while (!s1.empty()) {
		top = s1.top();
		s2.push(top);
		s1.pop();
	}

	top = s2.top();
	s2.pop();
	return top;
}

int main()
{
	SQueue<int> sq;

	for (int i = 0; i < 10; i++) {
		sq.enqueue(i);
	}

	for (int i = 0; i < 10; i++) {
		cout << sq.dequeue() << endl;
	}

	return 0;
}
