/*
 * =====================================================================================
 *
 *       Filename:  namespace.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/06/2015 02:45:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

// instroduce direct visibility of all the names of the std namespace
using namespace std;

namespace first {
	int x = 5;
}

namespace second {
	double x = 3.1416;
}

int main()
{
	{
	using namespace first;
	cout << x << endl;
	}
	

	using namespace second;
	cout << x << endl;
}
