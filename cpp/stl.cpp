/*
 * =====================================================================================
 *
 *       Filename:  stl.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/31/2015 03:25:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <functional> // including greater<int>()

using namespace std;

int main()
{
	int array[5];
	array[0] = 3;
	array[1] = 1;
	array[2] = 4;
	array[3] = 2;
	array[4] = 5;

	cout << "Before sort:" << endl;
	for (int i = 0; i < 5; ++i)
		cout << array[i];
	cout << endl;

	sort(array, array + 5);
	cout << "Default ascending sort:" << endl;
	for (int i = 0; i < 5; ++i)
		cout << array[i];
	cout << endl;

	sort(array, array + 5, greater<int>());
	cout << "Descending sort:" << endl;
	for (int i = 0; i < 5; ++i)
		cout << array[i];
	cout << endl;

	return 0;
}
