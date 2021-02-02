#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *x;
	int rt;
	int shm_id;
	char *addnum = "myadd";
	char *ptr;

	pthread_mutex_t mutex;
	pthread_mutexattr_t mutexattr;

	pthread_mutexattr_init(&mutexattr);
	pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);

	rt = fork();
	if (rt == 0) {
		shm_id = shm_open(addnum, O_RDWR, 0);
		ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED,
				shm_id, 0);
		x = (int *)ptr;

		for (int i = 0; i < 10; i++) {
			pthread_mutex_lock(&mutex);
			(*x)++;
			printf("x++:%d\n", *x);
			pthread_mutex_unlock(&mutex);
			sleep(1);
		}
	} else {
		shm_id = shm_open(addnum, O_RDWR | O_CREAT, 0644);
		ftruncate(shm_id, sizeof(int));
		ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED,
				shm_id, 0);
		x = (int *)ptr;

		for (int i = 0; i < 10; i++) {
			pthread_mutex_lock(&mutex);
			(*x) += 2;
			printf("x+=2:%d\n", *x);
			pthread_mutex_unlock(&mutex);
			sleep(1);
		}
	}

//	sleep(10);

	shm_unlink(addnum);
	munmap(ptr, sizeof(int));

	return 0;
}
