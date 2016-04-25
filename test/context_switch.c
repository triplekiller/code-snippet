/*
 * =====================================================================================
 *
 *       Filename:  context_switch.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/19/2015 02:17:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int pri_max, data, i, iter_cnt;
	int pfd1[2], pfd2[2], time_pipe[2];

	struct timeval begin, end;
	struct sched_param pri_param;
	pid_t pid, child;

	cpu_set_t cpuset;

	if (argc > 1)
		iter_cnt = atoi(argv[1]);
	else
		iter_cnt = 10000;

	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);

	memset(&pri_param, 0, sizeof(struct sched_param));

	pid = getpid();

	// force the process running on CPU0
	if (sched_setaffinity(pid, sizeof(cpu_set_t), &cpuset) < 0) {
		perror("sched_setaffinity");
		exit(EXIT_FAILURE);
	}

	// RT sched: SCHED_FIFO/SCHED_RR (static priority: 1~99)
	// normal sched: SCHED_OTHER/SCHED_BATCH/SCHED_IDLE (static priority: 0)
	if ((pri_max = sched_get_priority_max(SCHED_FIFO)) < 0) {
		perror("sched_get_priority_max");
		exit(EXIT_FAILURE);
	}

	printf("pri_max for SCHED_FIFO is %d\n", pri_max);

	pri_param.sched_priority = pri_max;

	if (sched_setscheduler(pid, SCHED_FIFO, &pri_param) < 0) {
		perror("sched_setscheduler");
		exit(EXIT_FAILURE);
	}

	if (pipe(pfd1) < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	if (pipe(pfd2) < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	if (pipe(time_pipe) < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	child = fork();
	if (child < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (child == 0) {
		int n = sizeof(data);
		close(pfd1[1]);
		close(pfd2[0]);
		close(time_pipe[0]);

		for (i = 0; i < iter_cnt; ++i) {
			if (read(pfd1[0], &data, sizeof(data)) != n) {
				perror("read");
				exit(EXIT_FAILURE);
			}

			if (write(pfd2[1], &data, sizeof(data)) != n) {
				perror("write");
				exit(EXIT_FAILURE);
			}
		}

		gettimeofday(&end, NULL);

		n = sizeof(struct timeval);
		if (write(time_pipe[1], &end, sizeof(struct timeval)) != n) {
			perror("write time_pipe at child process");
			exit(EXIT_FAILURE);
		}

		close(pfd1[0]);
		close(pfd2[1]);
		close(time_pipe[1]);
		exit(EXIT_FAILURE);
	} else {
		double switch_time;
		int n;
		close(pfd1[0]);
		close(pfd2[1]);
		close(time_pipe[1]);

		data = 1;
		n = sizeof(data);
		gettimeofday(&begin, NULL);

		for (i = 0; i < iter_cnt; ++i) {
			if (write(pfd1[1], &data, sizeof(data)) != n) {
				perror("write at parent process");
				exit(EXIT_FAILURE);
			}

			if (read(pfd2[0], &data, sizeof(data)) !=n ) {
				perror("read at parent process");
				exit(EXIT_FAILURE);
			}
		}

		n = sizeof(struct timeval);
		if (read(time_pipe[0], &end, sizeof(struct timeval)) != n) {
			perror("read time_pipe at parent process");
			exit(EXIT_FAILURE);
		}

		close(pfd1[1]);
		close(pfd2[0]);
		close(time_pipe[0]);

		wait(NULL);
		switch_time = (end.tv_sec - begin.tv_sec) * 1000000 + (end.tv_usec
			- begin.tv_usec);
		switch_time = switch_time / iter_cnt / 2;

		printf("context switch between two processes: %0.6lfus\n", switch_time);
	}

	return 0;
}
