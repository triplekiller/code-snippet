/*
 * =====================================================================================
 *
 *       Filename:  subject.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/08/2015 04:46:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>
#include <list>
#include "observer.h"

class Subject {
public:
	void attach(Shop *sp);
	void detach(Shop *sp);
	void notify(Shop *sp);

private:
	std::vector<Shop *> vs;
};

class DummyProduct : public Subject {
public:
	void changePrice(float price) {
		notify(price);
	}
};
