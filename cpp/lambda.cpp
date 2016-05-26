/*
 * =====================================================================================
 *
 *       Filename:  lamada.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/07/2015 02:44:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>

int main()
{
	std::vector<int> vec(10);
//	std::iota(vec.begin(), vec.end(), 1);

	std::cout << "original data:" << std::endl;
	// C++11 does not support generic lambda
	// C++14 allows lambda function parameters to be declared with auto
	std::for_each(vec.begin(), vec.end(),
		[](std::vector<int>::iterator i) {
			std::cout << *i << " ";
		});
	std::cout << std::endl;

//	std::sort(vec.begin(), vec.end(), [](auto i, auto j){ return (i > j); });
//	std::for_each(vec.begin(), vec.end(), [](auto i){ std::cout << i << " "; });
	std::cout << std::endl;

	std::vector<std::string> v;
	v.push_back("cat");
	v.push_back("antelope");
	v.push_back("puppy");
	v.push_back("bear");

	std::sort(v.begin(), v.end(),
		[](const std::string &left, const std::string &right) {
			return left.size() < right.size();
		});

	for (auto &i : v) {
		std::cout << i << std::endl;
	}

	return 0;
}
