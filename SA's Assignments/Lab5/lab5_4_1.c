#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define ARR_SIZE 10
#define NUM_THREADS 5

pthread_mutex_t mutex_sum;
long int A[ARR_SIZE];
long int sum;
pthread_t threads[1000];

void * calc_sum(void *);

int main()
{
	int status;
	long int i;
	long int t_no;
	pthread_attr_t attr;

	pthread_mutex_init(&mutex_sum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	sum = 0;

	for (i = 0; i < ARR_SIZE; i++) {
		scanf("%ld", &A[i]);
	}
	
	for (i = 0; i < NUM_THREADS; i++) {
		t_no = i;

		status = pthread_create(&threads[i], &attr, calc_sum, (void *) t_no);

		if (status) {
			printf("ERROR: Return code from pthread_create() is %d\n", status);
			exit(EXIT_FAILURE);
		}
	}

	pthread_attr_destroy(&attr);

	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("Total Sum = %ld\n", sum);

	pthread_mutex_destroy(&mutex_sum);
	pthread_exit(NULL);
				
	return 0;
}

void * calc_sum(void * t_no)
{
	long int t_n;
	long int i;
	long int temp;
	long int partial_sum;
	
	temp = ARR_SIZE / NUM_THREADS;
	
	t_n = (long int) t_no;
	partial_sum = 0;

	pthread_mutex_lock(&mutex_sum);

	for (i = t_n * temp; i < (t_n * temp) + temp; i++) {
		sum += A[i];
		partial_sum += A[i];
	}
	
	printf("Thread #%ld calculated partial sum = %ld\n", t_n, partial_sum);

	pthread_mutex_unlock(&mutex_sum);

	pthread_exit((void *) 0);
}
