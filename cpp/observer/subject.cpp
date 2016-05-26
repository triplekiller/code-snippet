/*
 * =====================================================================================
 *
 *       Filename:  subject.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/08/2015 04:46:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <algorithm>
#include "subject.h"

using namespace std;

void Subject::attach(Shop *sp)
{
	vs.push_back(sp);
}

void Subject::detach(Shop *sp)
{
	vs.erase(remove(vs.begin(), vs.end(), sp), vs.end());
}

void Subject::notify(float price)
{
	vector<Shop *>::const_iterator iter;
	for (iter = vs.begin(); iter != vs.end(); ++iter) {
		if (*iter != 0)
			(*iter)->update(price);
	}
}
