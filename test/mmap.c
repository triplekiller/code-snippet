/*
 * =====================================================================================
 *
 *       Filename:  mmap.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/29/2015 02:06:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>

int main()
{
	char *p = mmap(NULL, 50 << 20, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_SHARED, -1, 0);

	int i = 0;
	for (i = 0; i < (50 << 20) / 4096; i++)
		p[i * 4096] = i;

	sleep(1000000);

	return 0;
}
