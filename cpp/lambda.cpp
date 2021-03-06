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

//With "lambda," we use higher-order procedures. A lambda contains no statements.
//It returns a single expression. This limitation leads to simpler logic.

// lambdas are just function objects automatically created by the compiler.
// a generic lambda is a function template. (Since C++14)


// The difference of the usage of functions and lambda functions boils down to
// two points.
//
// 1. You can not overload lambdas.
// 2. A lambda function can capture local variables.

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
