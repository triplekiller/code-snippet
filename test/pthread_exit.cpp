#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif

#include <pthread.h>
#include <semaphore.h>

#ifdef __cplusplus
}
#endif

sem_t sem1, sem2, sem3;

void *func_a(void *ptr)
{
	int id = *(int *)ptr;
	int i = 0;
	for (i = 0; i < 3; ++i) {
		sem_wait(&sem1);
		cout << "A-" << hex << id << endl;
		sem_post(&sem2);
	}

	return NULL;
}

void *func_b(void *ptr)
{
	int id = *(int *)ptr;
	int i = 0;
	for (i = 0; i < 3; ++i) {
		sem_wait(&sem2);
		cout << "B-" << hex << id << endl;
		sem_post(&sem3);
	}

	return NULL;
}

void *func_c(void *ptr)
{
	int id = *(int *)ptr;
	int i = 0;
	for (i = 0; i < 3; ++i) {
		sem_wait(&sem3);
		cout << "C-" << hex << id << endl;
		sem_post(&sem1);
	}

	return NULL;
}

int main()
{
	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);
	sem_init(&sem3, 0, 0);

	pthread_t t1, t2, t3;
	pthread_create(&t1, NULL, &func_a, (void *)&t1);
	pthread_create(&t2, NULL, &func_b, (void *)&t2);
	pthread_create(&t3, NULL, &func_c, (void *)&t3);

	sem_post(&sem1);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

#if 0
	while (1) {
		sleep(10);
	}
#endif

	return 0;
}
