/*
 * =====================================================================================
 *
 *       Filename:  1-1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  09/01/2015 10:18:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <set>
#include <cstring>
#include <cassert>

using namespace std;

// using set container
bool isUniqueStr(const char *s)
{
	if (!s)
		return false;

	set<char> charSet;
	int len = strlen(s);
	for (int i = 0; i < len; ++i)
		charSet.insert(s[i]);

	if (charSet.size() == len)
		return true;
	else
		return false;
}

bool inRange(char c, const char *str)
{
	assert(str);

	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (str[i] == c)
			return true;
	}

	return false;
}

bool checkUnique(const char *s)
{
	assert(s);

	int len = strlen(s);
	char tmp[len];
	int j = 0;
	for (int i = 0; i < len; ++i) {
		if (inRange(s[i], tmp))
			continue;
		else
			tmp[j++] = s[i];
	}

	if (strlen(tmp) == len)
		return true;
	else
		return false;
}

bool isUnique(const char *s)
{
	assert(s);

	int len = strlen(s);
	for (int i = 0; i < len; ++i) {
		for (int j = i + 1; j < len; ++j) {
			if (s[i] == s[j])
				return false;
		}
	}

	return true;
}

// bitmap
bool isUnique2(string &s)
{
	int a[8];
	memset(a, 0, sizeof(a));
	int len = s.length();

	for (int i = 0; i < len; ++i) {
		int v = (int)s[i];
		int idx = v / 32;
		int shift = v % 32;
		if (a[idx] & (1 << shift))
			return false;

		a[idx] |= (1 << shift);
	}

	return true;
}

int main()
{
	const char *str1 = "hello";
	const char *str2 = "world";
	const char *str3 = "gogogo";
	string s = "fuck^";

	cout << str3 << ' ' << isUniqueStr(str3) << endl;
	cout << str2 << ' ' << checkUnique(str2) << endl;
	cout << str1 << ' ' << isUnique(str1) << endl;
	cout << s << ' ' << isUnique2(s) << endl;

	return 0;
}
