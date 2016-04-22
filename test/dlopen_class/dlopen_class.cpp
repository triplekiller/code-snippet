/*
 * =====================================================================================
 *
 *       Filename:  dlopen_class.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/11/2015 10:23:23 AM
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
#include "polygon.hpp"

using namespace std;

int main()
{
	void *handle = dlopen("./triangle.so", RTLD_LAZY);

	create_t *create_triangle = (create_t *)dlsym(handle, "create");
	destroy_t *destroy_triangle = (destroy_t *)dlsym(handle, "destroy");

	polygon *poly = create_triangle();
	poly->setSideLength(7);

	cout << "The area is: " << poly->getArea() << endl;

	destroy_triangle(poly);

	dlclose(handle);

	return 0;
}
