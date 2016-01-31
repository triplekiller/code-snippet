/*
 * =====================================================================================
 *
 *       Filename:  ordering.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/03/2015 07:59:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <sched.h>

#define MT_IA 397
#define MT_LEN 624

#define USE_CPU_FENCE 1

class MersenneTwister
{
	unsigned int m_buffer[MT_LEN];
	int m_index;

public:
	MersenneTwister(unsigned int seed);
	unsigned int integer() __attribute__((noinline));
};

MersenneTwister::MersenneTwister(unsigned int seed)
{
	for (int i = 0; i < MT_LEN; i++)
		m_buffer[i] = seed;

	m_index = 0;
	for (int i = 0; i < MT_LEN * 100; i++)
		integer();
}

unsigned int MersenneTwister::integer()
{
	int i = m_index;
	int i2 = m_index + 1;
	if (i2 >= MT_LEN)
		i2 = 0;

	int j = m_index + MT_IA;
	if (j > MT_LEN)
		j -= MT_LEN;

	unsigned int s = (m_buffer[i] & 0x80000000) | (m_buffer[i2] & 0x7fffffff);
	unsigned int r = m_buffer[j] ^ (s >> 1) ^ ((s & 1) * 0x9908B0DF);
	m_buffer[m_index] = r;
	m_index = i2;

	r ^= (r >> 11);
	r ^= (r << 7) & 0x9d2c5680UL;
	r ^= (r << 15) & 0xefc60000UL;
	r ^= (r >> 18);

	return r;
}

sem_t beginSema1;
sem_t beginSema2;
sem_t endSema;

int x, y;
int r1, r2;

void *thread1Func(void *param)
{
	MersenneTwister random(1);
	for (;;)
	{
		sem_wait(&beginSema1);
		while (random.integer() % 8 != 0);

		x = 1;

#if USE_CPU_FENCE
		asm volatile("mfence":::"memory");
#else
		asm volatile("":::"memory");
#endif

		r1 = y;

		sem_post(&endSema);
	}

	return NULL;
}

void *thread2Func(void *param)
{
	MersenneTwister random(2);
	for (;;)
	{
		sem_wait(&beginSema2);
		while (random.integer() % 8 != 0);

		y = 1;
#if USE_CPU_FENCE
		asm volatile("mfence":::"memory");
#else
		asm volatile("":::"memory");
#endif

		r2 = x;

		sem_post(&endSema);
	}

	return NULL;
}

int main()
{
	sem_init(&beginSema1, 0, 0);
	sem_init(&beginSema2, 0, 0);
	sem_init(&endSema, 0, 0);

	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, thread1Func, NULL);
	pthread_create(&thread2, NULL, thread2Func, NULL);

#if 0
	cpu_set_t cpus;
	CPU_ZERO(&cpus);
	CPU_SET(0, &cpus);
	pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpus);
	pthread_setaffinity_np(thread2, sizeof(cpu_set_t), &cpus);
#endif

	int detected = 0;
	for (int iter = 1; ; iter++)
	{
		x = 0;
		y = 0;

		// signal both threads
		sem_post(&beginSema1);
		sem_post(&beginSema2);
		// wait for both threads
		sem_wait(&endSema);
		sem_wait(&endSema);
		// check if there was a simultaneous reorder
		if (r1 == 0 && r2 == 0)
		{
			detected++;
			printf("%d reorders detected after %d iterations\n",
				detected, iter);
		}
	}

	return 0;
}
