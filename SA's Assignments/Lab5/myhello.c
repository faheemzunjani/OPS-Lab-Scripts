#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 10

void * print_hello(void *);

int main()
{
	pthread_t threads[1000];
	int t_n;
	int status;
	long i;

	for (i = 0; i < NUM_THREADS; i++) {
		status = pthread_create(&threads[i], NULL, print_hello, (void *) i);

		if (status) {
			printf("ERROR: Return code from pthread_create() is %d\n", status);
			exit(EXIT_FAILURE);
		}
	}

	pthread_exit(NULL);
				
	return 0;
}

void * print_hello(void * thread_no)
{
	long t_no;

	t_no = (long) thread_no;

	printf("hello world from thread #%ld\n", t_no);

	pthread_exit(NULL);
}
