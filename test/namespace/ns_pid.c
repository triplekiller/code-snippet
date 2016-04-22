/*
 * =====================================================================================
 *
 *       Filename:  ns_ipc.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/08/2015 12:03:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

int checkpoint[2];
static char child_stack[STACK_SIZE];
char *const child_args[] = {
	"/bin/bash",
	NULL
};

int child_main(void *arg)
{
	char c;
	close(checkpoint[1]);
	read(checkpoint[0], &c, 1);
	printf(" - [%5d] World !\n", getpid());
	sethostname("In Namespace", 12);
	execv(child_args[0], child_args);
	printf("oops\n");
}

int main()
{
	pipe(checkpoint);
	printf(" - [%5d] Hello ?\n", getpid());
	int child_pid = clone(child_main, child_stack+STACK_SIZE, CLONE_NEWUTS |
		CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD, NULL);
	close(checkpoint[1]);
	waitpid(child_pid, NULL, 0);

	return 0;
}
