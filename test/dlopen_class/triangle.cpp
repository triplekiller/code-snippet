/*
 * =====================================================================================
 *
 *       Filename:  triangle.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/11/2015 10:37:42 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <dlfcn.h>
#include <math.h>
#include "polygon.hpp"

using namespace std;

class triangle : public polygon
{
public:
	virtual double getArea() const {
		return sideLength * sideLength * sqrt(3) / 2;
	}
};

extern "C" polygon *create()
{
	return new triangle;
}

extern "C" void destroy(polygon *p)
{
	delete p;
}
