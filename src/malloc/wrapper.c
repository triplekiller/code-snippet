/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/11/2015 11:31:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 1) {
		printf("You must supply a program to be invoked to use your replacement"
			" malloc() script.\n");
		printf("...you may use any program, even system programs, such as `ls`.\n");
		printf("\n");
		printf("Example: %s /bin/ls\n", argv[0]);
		return 1;
	}

	char **env = malloc(2 * sizeof(char *));
	env[0] = malloc(100 * sizeof(char));
	sprintf(env[0], "LD_PRELOAD=./malloc.so");
	env[1] = NULL;
	 
	execve(argv[1], argv + 1, env);
	perror("exec() failed");

	free(env[0]);
	free(env);

	return 2;
}
