/*
 * =====================================================================================
 *
 *       Filename:  permutation.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/05/2015 10:01:59 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

// http://blog.csdn.net/morewindows/article/details/7370155

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void swap(char *a, char *b)
{
	char t = *a;
	*a = *b;
	*b = t;
}

bool isSwap(char *str, int begin, int end)
{
	for (int i = begin; i < end; i++) {
		if (str[i] == str[end])
			return false;
	}

	return true;
}

// m is the total number
void allRange(char *str, int k, int m)
{
	if (k == m) {
		static int cnt = 1;
		printf("The %dth permutation: %s\n", cnt++, str);
	} else {
		for (int i = k; i <= m; i++) {
			if (isSwap(str, k, i)) {
				swap(str + k, str + i);
				allRange(str, k + 1, m);
				swap(str + k, str + i);
			}
		}
	}
}

void permutation(char *str)
{
	if (!str)
		return;
	allRange(str, 0, strlen(str) - 1);
}

int main(int argc, char **argv)
{
	char str[] = "1223";
	const char *s = "abcd";
	permutation(str);

	return 0;
}
