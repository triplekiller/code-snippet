/*
 * =====================================================================================
 *
 *       Filename:  qstack.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/08/2015 01:46:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <deque>

using namespace std;

template<typename T>
class QStack
{
public:
	QStack() {}
	~QStack() {}

	void push(const T&);
	T pop();

private:
	deque<T> q1, q2;
};

template<typename T>
void QStack<T>::push(const T& x)
{
	q1.push_back(x);
}

template<typename T>
T QStack<T>::pop()
{
	T first;
	if (q2.empty()) {
		while (!q1.empty()) {
			first = q1.front();
			q2.push_front(first);
			q1.pop_front();
		}
	}

	if (!q2.empty()) {
		first = q2.front();
		q2.pop_front();
		return first;
	}
}

int main()
{
	QStack<int> qs;

	for (int i = 0; i < 10; i++)
		qs.push(i);

	for (int i = 0; i < 10; i++)
		cout << qs.pop() << endl;

	return 0;
}
