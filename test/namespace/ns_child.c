/*
 * =====================================================================================
 *
 *       Filename:  ns_child.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/23/2015 03:48:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

#define exit_err(msg) do { \
	perror(msg); \
	exit(EXIT_FAILURE); \
} while(0)

static void usage(char *name)
{
	fprintf(stderr, "Usage: %s [options] cmd [arg...]\n", name);
	fprintf(stderr, "Options can be:\n");
	fprintf(stderr, "    -i   new IPC namespace\n");
	fprintf(stderr, "    -m   new mount namespace\n");
	fprintf(stderr, "    -n   new network namespace\n");
	fprintf(stderr, "    -p   new PID namespace\n");
	fprintf(stderr, "    -u   new UTS namespace\n");
	fprintf(stderr, "    -U   new user namespace\n");
	fprintf(stderr, "    -v   Display verbose messages\n");
	exit(EXIT_FAILURE);
}

static int child_func(void *arg)
{
	char **argv = arg;

	execvp(argv[0], &argv[0]);
	exit_err("execvp");
}

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];

int main(int argc, char **argv)
{
	int flags, opt, verbose;
	pid_t child_pid;

	flags = verbose = 0;

	while ((opt = getopt(argc, argv, "+imnpuUv")) != -1) {
		switch (opt) {
		case 'i':
			flags |= CLONE_NEWIPC;
			break;
		case 'm':
			flags |= CLONE_NEWNS;
			break;
		case 'n':
			flags |= CLONE_NEWNET;
			break;
		case 'p':
			flags |= CLONE_NEWPID;
			break;
		case 'u':
			flags |= CLONE_NEWUTS;
			break;
		case 'U':
			flags |= CLONE_NEWUSER;
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			usage(argv[0]);
        }
    }

	child_pid = clone(child_func, child_stack + STACK_SIZE, flags | SIGCHLD,
		&argv[optind]);

	if (child_pid == -1)
		exit_err("clone");

	if (verbose)
		printf("%s: PID of child created by clone is %ld\n", argv[0], (long)child_pid);

	if (waitpid(child_pid, NULL, 0) == -1)
		exit_err("waitpid");

	if (verbose)
		printf("%s: terminating\n", argv[0]);

	exit_err(EXIT_SUCCESS);
}
