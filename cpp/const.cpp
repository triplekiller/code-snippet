/*
 * =====================================================================================
 *
 *       Filename:  const.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/22/2015 08:56:35 PM
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

#define PI 3.14

const double pi = 3.14;

int main()
{
	double i = PI;
	double j = PI;
	double k = pi;
	double m = pi;

	cout << &i << endl;
	cout << &j << endl;
	cout << &k << endl;
	cout << &m << endl;

	return 0;
}
