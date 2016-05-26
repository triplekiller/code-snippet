/*
 * =====================================================================================
 *
 *       Filename:  thread.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/07/2015 10:14:32 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void func(int tid)
{
	cout << "launched by thread-" << tid << endl;
}

int main()
{
	vector<thread> th;
	int num = 10;

	for (int i = 0; i < num; ++i) {
		th.push_back(thread(func, i));
	}

	for (auto &t : th) {
		t.join();
	}

	return 0;
}
