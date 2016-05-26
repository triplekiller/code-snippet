/*
 * =====================================================================================
 *
 *       Filename:  friend.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/23/2015 03:21:06 PM
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

class Rectangle {
public:
	Rectangle() {}
	Rectangle(int x, int y) : width(x), height(y) {}

	int area() { return width * height; }
	// non-member method accesses the private member of a class
	friend Rectangle duplicate(const Rectangle &obj);

private:
	int width, height;
};

Rectangle duplicate(const Rectangle &obj)
{
	Rectangle res;
	res.width = obj.width * 2;
	res.height = obj.height * 2;

	return res;
}

int main()
{
	Rectangle foo;
	Rectangle bar(2, 3);
	foo = duplicate(bar);

	cout << "foo.area()=" << foo.area() << endl;
	
	return 0;
}
