/*
 * =====================================================================================
 *
 *       Filename:  backtrace.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  06/18/2014 09:49:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include <signal.h>
#include <stdio.h>

void sigsegv_handler(int signum)
{
	printf("#sigsegv# receive SIGSEGV signal\n");

	void *array[30];
	size_t size, i;
	char **str;

	size = backtrace(array, 30);
	str = backtrace_symbols(array, size);
	printf("#sigsegv# obtained %d stack frames\n", size);

	for (i = 0; i < size; i++)
		printf("%s\n", str[i]);

	free(str);
	exit(0);
}

void func_a()
{
	*((volatile char *)0x0) = 0x123;
}

void func_b()
{
	func_a();
}

void func_c()
{
	func_b();
}

int main()
{
	signal(SIGSEGV, sigsegv_handler);
	func_c();

	return 0;
}
