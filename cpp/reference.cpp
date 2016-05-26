/*
 * =====================================================================================
 *
 *       Filename:  reference.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/22/2014 12:41:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using namespace std;

int main()
{
	int a = 10;
	int &b = a;

	cout << &a << endl;
	cout << &b << ":" << sizeof(b) << endl;
	cout << b << endl;

	return 0;
}
