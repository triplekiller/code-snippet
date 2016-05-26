/*
 * =====================================================================================
 *
 *       Filename:  async.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/08/2015 02:40:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


// http://www.drdobbs.com/cpp/c11s-async-template/240001196?pgno=2

#include <future>
#include <iostream>
#include <vector>

int main()
{
	std::vector<std::future<int>> futures;

	for (int i = 0; i < 10; ++i)
		futures.push_back(std::async([](int m){ return 2 * m; }, i));

	for (auto &e : futures)
		std::cout << e.get() << std::endl;

	return 0;
}
