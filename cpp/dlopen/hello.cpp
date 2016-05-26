/*
 * =====================================================================================
 *
 *       Filename:  hello.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/11/2015 09:05:07 AM
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

extern "C" void hello()
{
	std::cout << "#### hello world" << std::endl;
}

int main()
{
	char *ptr1 = NULL;
	char *ptr2 = nullptr;

	if (ptr1 == ptr2)
		cout << "equal" << endl;
	else
		cout << "nonequal" << endl;

	return 0;
}
