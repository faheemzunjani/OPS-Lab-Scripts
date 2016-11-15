#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define NUM_THREADS 32

void * print_priority(void *);

int main()
{
	pthread_t threads[1000];
	long priority_value;
	int status;
	long i;
	time_t t;

	srand((unsigned int) t);
	
	for (i = 0; i < NUM_THREADS; i++) {
		priority_value = rand() % NUM_THREADS;

		status = pthread_create(&threads[i], NULL, print_priority, (void *) priority_value);

		if (status) {
			printf("ERROR: Return code from pthread_create() is %d\n", status);
			exit(EXIT_FAILURE);
		}
	}

	pthread_exit(NULL);
				
	return 0;
}

void * print_priority(void * p_v)
{
	long priority_value;
	int i;

	priority_value = (long) p_v;

	printf("Thread with assigned priority %ld\n", priority_value);

	pthread_exit(NULL);
}
