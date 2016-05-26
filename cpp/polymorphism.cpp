/*
 * =====================================================================================
 *
 *       Filename:  polymorphism.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/24/2015 04:21:05 PM
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

class Polygon {
public:
	Polygon(int a, int b) : width(a), height(b) {}
	virtual int area(void) = 0;
	void printArea() { cout << this->area() << endl; }

protected:
	int width, height;
};

class Rectangle : public Polygon {
public:
	Rectangle(int a, int b) : Polygon(a, b) {}
	int area() { return width * height; }
};

class Triangle : public Polygon {
public:
	Triangle(int a, int b) : Polygon(a, b) {}
	int area() { return width * height / 2; }
};

int main()
{
	Polygon *ptr1 = new Rectangle(4, 5);
	Polygon *ptr2 = new Triangle(4, 5);

	ptr1->printArea();
	ptr2->printArea();

	delete ptr1;
	delete ptr2;

	return 0;
}
