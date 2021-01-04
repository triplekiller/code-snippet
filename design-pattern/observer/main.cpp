/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/08/2015 04:54:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include "subject.h"
#include "observer.h"

int main()
{
	DummyProduct product;

	Shop shop1("shop-1");
	Shop shop2("shop-2");

	pruduct.attach(&shop1);
	pruduct.attach(&shop2);

	product.changePrice(23.0f);
	product.detach(&shop2);
	product.changePrice(26.0f);

	return 0;
}
