#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex_sum;
long int A[100][100];
long int total;
pthread_t threads[1000];
int r;
int c;

void * threadSum(void *);

int main()
{
	int status;
	long int i;
	long int j;
	long int t_no;
	pthread_attr_t attr;
	int num_t;

	pthread_mutex_init(&mutex_sum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	total = 0;

	scanf("%d %d", &r, &c);

	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			scanf("%ld", &A[i][j]);
		}
	}
	
	num_t = r;
	
	for (i = 0; i < num_t; i++) {
		t_no = i;

		status = pthread_create(&threads[i], &attr, threadSum, (void *) t_no);

		if (status) {
			printf("ERROR: Return code from pthread_create() is %d\n", status);
			exit(EXIT_FAILURE);
		}
	}

	pthread_attr_destroy(&attr);

	for (i = 0; i < num_t; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("Total Sum = %ld\n", total);

	pthread_mutex_destroy(&mutex_sum);
	pthread_exit(NULL);
				
	return 0;
}

void * threadSum(void * t_no)
{
	long int t_n;
	long int i;
	long int partial_sum;
		
	t_n = (long int) t_no;
	partial_sum = 0;

	pthread_mutex_lock(&mutex_sum);
	
	for (i = 0; i < c; i++) {
		partial_sum += A[t_n][i];
	}

	total += partial_sum;

	pthread_mutex_unlock(&mutex_sum);

	pthread_exit((void *) 0);
}
