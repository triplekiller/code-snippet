/*
 * =====================================================================================
 *
 *       Filename:  regex.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/07/2015 10:32:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <regex>
#include <string>

using namespace std;

// regex supported in GCC 4.9

int main()
{
	string input;
	regex str("(\+|-)?[[:digit:]]+");
	while (true) {
		cout << "Input an integer:" << endl;
		cin >> input;
		if (!cin)
			break;
		if (input == "q")
			break;
		if (regex_match(input, str))
			cout << "integer" << endl;
		else
			cout << "invalid input" << endl;
	}

	return 0;
}
