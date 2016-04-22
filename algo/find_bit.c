/*
 * =====================================================================================
 *
 *       Filename:  find_bit.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/13/2015 04:56:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdio.h>

// search from LSB to MSB
int find_first_bit1(int a)
{
	int pos = 0;

	if ((a & 0x0000FFFF) == 0) {
		a >>= 16;
		pos += 16;
	}

	if ((a & 0x00FF) == 0) {
		a >>= 8;
		pos += 8;
	}

	if ((a & 0x0F) == 0) {
		a >>= 4;
		pos += 4;
	}

	if ((a & 0x3) == 0) {
		a >>= 2;
		pos += 2;
	}

	if ((a & 0x1) == 0) {
		a >>= 1;
		pos += 1;
	}

	if (a == 0)
		pos = -1;

	return pos;
}

int main()
{
//	int a = 0;
//	int a = 4096;
	int a = 0x80000000;
	printf("first bit one: %d\n", find_first_bit1(a));

	return 0;
}
