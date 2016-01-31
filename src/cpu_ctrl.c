/*
 * =====================================================================================
 *
 *       Filename:  cpu_ctrl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/17/2015 09:31:04 AM
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
#include <math.h>

#define SLEEP_TIME_US 10000

#define SINX_CYCLE_MS 100000
#define SINX_CNT 100

/* y = 0.5*(1+sin(ax+b)) */
void cpu_sinx()
{
	int i;
	long long busy_time[SINX_CNT], idle_time[SINX_CNT];
	struct timeval tv;
	long long start_time, end_time;

	for (i = 0; i < SINX_CNT; i++) {
		busy_time[i] = SINX_CYCLE_MS * 0.5 * (sin(6.2831 / SINX_CNT * i) + 1);
		idle_time[i] = SINX_CYCLE_MS - busy_time[i];
	}

	i = 0;
	while (1) {
		gettimeofday(&tv, NULL);
		start_time = tv.tv_sec * 1000000 + tv.tv_usec;
		end_time = start_time;

		while (end_time - start_time < busy_time[i]) {
			gettimeofday(&tv, NULL);
			end_time = tv.tv_sec * 1000000 + tv.tv_usec;
		}

		usleep(idle_time[i]);
		i = (i + 1) % 100;
	}
}

/* 50% cpu usage
 * time ./cpu_ctrl
 * cpu_usage = (user + sys) / real
 */
int main()
{
#if 0
	struct timeval tv;
	long long start_time, end_time;

	while (1) {
		gettimeofday(&tv, NULL);
		start_time = end_time = tv.tv_sec * 1000000 + tv.tv_usec;

		/* busy */
		while (end_time - start_time < SLEEP_TIME_US) {
			gettimeofday(&tv, NULL);
			end_time = tv.tv_sec * 1000000 + tv.tv_usec;
		}

		/* idle */
		usleep(SLEEP_TIME_US);
	}
#endif

	cpu_sinx();
}
