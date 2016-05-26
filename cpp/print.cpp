/*
 * =====================================================================================
 *
 *       Filename:  print.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/22/2016 10:21:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>

#define LIKELY(x) __builtin_expect((x), true)
#define UNLIKELY(x) __builtin_expect((x), false)

#define CHECK(x) \
	if (LIKELY(x)) \
		; \
	else \
		std::cout << "Check failed: " #x << " "

int main()
{
	int a = 0;

	CHECK(a) << a << std::endl;

	return 0;
}
