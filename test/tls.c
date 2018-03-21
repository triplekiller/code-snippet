#include <stdio.h>
#include <malloc.h>
#include <pthread.h>

// TLS = Thread Local Storage
// TSD = Thread Specific Data

static pthread_key_t log_key;

void write_log(const char *msg)
{
	FILE *log = (FILE *)pthread_getspecific(log_key);
	fprintf(log, "%s\n", msg);
}

void close_log(void *log)
{
	fclose((FILE *)log);
}

void *thread_func(void *args)
{
	char log_file[20];
	FILE *log;

	sprintf(log_file, "thread_%08x.log", (int)pthread_self());
	log = fopen(log_file, "w");
	pthread_setspecific(log_key, log);
	printf("log_key=%d in thread %08x\n", (int)log_key, (int)pthread_self());
	write_log("Thread starting");

	return NULL;
}

int main()
{
	int i;
	pthread_t threads[5];

	pthread_key_create(&log_key, close_log);
	printf("log_key=%d in main\n", (int)log_key);

	for (i = 0; i < 5; ++i) {
		pthread_create(&threads[i], NULL, thread_func, NULL);
	}

	for (i = 0; i < 5; ++i) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}
