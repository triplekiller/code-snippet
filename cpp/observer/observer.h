/*
 * =====================================================================================
 *
 *       Filename:  observer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/08/2015 04:39:23 PM
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

class Observer {
public:
	virtual void update(float price) = 0;
};

class Shop : public Observer {
public:
	Shop(string n) { name = n; }
	void update(float p) {
		price = p; 
		cout << name << " price is " << price << endl;
	}

private:
	string name;
	float price;
};
