/*
 * =====================================================================================
 *
 *       Filename:  string.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/06/2015 09:29:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main(void)
{
	string str1 = "hello world"; // string str1("hello world");
	string str2 = str1; // calling copy ctor

	cout << "str1 addr: " << static_cast<void *>(&str1) << ' ' << str1.c_str() << endl;
	cout << "str2 addr: " << static_cast<void *>(&str2) << ' ' << str2.c_str() << endl;
	printf("str1: %p\n", str1.c_str());
	printf("str2: %p\n", str2.c_str());

	str1[1] = 'q';
	str2[1] = 'w';

	cout << "after copy-on-write:" << endl;
	cout << "str1 addr: " << static_cast<void *>(&str1) << ' ' << str1.c_str() << endl;
	cout << "str2 addr: " << static_cast<void *>(&str2) << ' ' << str2.c_str() << endl;
	printf("str1: %p\n", str1.c_str());
	printf("str2: %p\n", str2.c_str());

	return 0;
}
