/*
 * =====================================================================================
 *
 *       Filename:  set.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/21/2015 10:22:11 PM
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
#include <set>
#include <algorithm>

using namespace std;

int main()
{
	set<string> strSet;
	set<string>::iterator si;

	strSet.insert("cantaloupe");
	strSet.insert("banana");
	strSet.insert("orange");
	strSet.insert("apple");
	strSet.insert("orange");
	strSet.insert("grape");
	strSet.insert("grape");

	for (si = strSet.begin(); si != strSet.end(); si++)
		cout << *si << " ";
	cout << endl;

	cout << endl << "Test for_each:" << endl;
	for_each(strSet.begin(), strSet.end(), [](string elem) {
		cout << (elem) << " ";});

	cout << endl;
	return 0;
}
