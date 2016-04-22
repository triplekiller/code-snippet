/*
 * =====================================================================================
 *
 *       Filename:  polygon.hpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/11/2015 10:24:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef _POLYGON_HPP
#define _POLYGON_HPP

class polygon
{
public:
	polygon() : sideLength(0) {}
	virtual ~polygon() {}

	void setSideLength(double len) { sideLength = len; }

	virtual double getArea() const = 0;

protected:
	double sideLength;
};

typedef polygon *create_t();
typedef void destroy_t(polygon *);

#endif
