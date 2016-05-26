/*
 * =====================================================================================
 *
 *       Filename:  bracket.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/01/2015 10:50:00 AM
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
#include <stack>
#include <map>
#include <set>

using namespace std;

// bracket type: {}, [], ()
// ([(2+11)]+)
// (4+{8-[22+8]*}]

bool isOpenBracket(char c, map<char, char> &charMap)
{
	auto iter = charMap.begin();
	while (iter != charMap.end()) {
		if (iter->second == c)
			return true;
		else
			iter++;
	}

	return false;
}

bool testBracket(const string &s)
{
	stack<char> bracketStack;
	map<char, char> bracketMap;

	bracketMap['}'] = '{';
	bracketMap[']'] = '[';
	bracketMap[')'] = '(';

	for (int i = 0; i < s.size(); ++i) {
		// encounter open bracket
		if (isOpenBracket(s[i], bracketMap))
			bracketStack.push(s[i]);

		// encounter closed bracket
		if (bracketMap.find(s[i]) != bracketMap.end()) {
			if (bracketStack.empty())
				return false;

			if (bracketMap[s[i]] != bracketStack.top())
				return false;
			else
				bracketStack.pop();
		}
	}

	if (bracketStack.size() > 0)
		return false;
	else
		return true;
}

int main()
{
	const string s = "([(2+11)]+)";
//	const string s = "(4+{8-[22+8]*}]";

	cout << testBracket(s) << endl;

	return 0;
}
