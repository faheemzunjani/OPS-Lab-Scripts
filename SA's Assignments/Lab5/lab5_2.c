#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define NUM_THREADS 32

void * calc_sin(void *);

int main()
{
	pthread_t threads[1000];
	int t_n;
	int status;
	long i;

	for (i = 0; i < NUM_THREADS; i++) {
		status = pthread_create(&threads[i], NULL, calc_sin, (void *) i);

		if (status) {
			printf("ERROR: Return code from pthread_create() is %d\n", status);
			exit(EXIT_FAILURE);
		}
	}

	pthread_exit(NULL);
				
	return 0;
}

void * calc_sin(void * thread_no)
{
	double sum;
	long t_no;
	int i;

	t_no = (long) thread_no;
	sum = 0;

	sleep(4);

	for (i = 1; i <= 10000; i++) {
		sum += sin(i);
	}
	
	printf("Sum of sin(i) in thread #%ld is %lf\n", t_no, sum);

	pthread_exit(NULL);
}
