#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 4
#define VECLEN 1000

struct dot_data {
	double *a;
	double *b;
	double sum;
	int veclen;
};

pthread_mutex_t mutex_sum;
long int sum;
pthread_t threads[NUM_THREADS];
struct dot_data dot_str;

void * dot_prod(void *);

int main()
{
	int status;
	long int i;
	double * a;
	double * b;
	long int t_no;
	pthread_attr_t attr;

	a = (double *) malloc(NUM_THREADS * VECLEN * sizeof (double));
	b = (double *) malloc(NUM_THREADS * VECLEN * sizeof (double));

	for (i = 0; i < VECLEN * NUM_THREADS; i++) {
		a[i] = 1.0;
		b[i] = a[i];
	}

	dot_str.veclen = VECLEN;
	dot_str.a = a;
	dot_str.b = b;
	dot_str.sum = 0;

	pthread_mutex_init(&mutex_sum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	for (i = 0; i < NUM_THREADS; i++) {
		t_no = i;

		status = pthread_create(&threads[i], &attr, dot_prod, (void *) t_no);

		if (status) {
			printf("ERROR: Return code from pthread_create() is %d\n", status);
			exit(EXIT_FAILURE);
		}
	}

	pthread_attr_destroy(&attr);

	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("Sum = %f\n", dot_str.sum);
	free(a);
	free(b);

	pthread_mutex_destroy(&mutex_sum);
	pthread_exit(NULL);
				
	return 0;
}

void * dot_prod(void * arg)
{
	int i;
	int start;
	int end;
	int len;
	long offset;
	double mysum;
	double *x;
	double *y;

	offset = (long) arg;

	len = dot_str.veclen;
	start = offset * len;
	end = start + len;
	x = dot_str.a;
	y = dot_str.b;
	mysum = 0;

	for (i = start; i < end; i++) {
		mysum += (x[i] * y[i]);
	}

	pthread_mutex_lock(&mutex_sum);

	dot_str.sum += mysum;

	pthread_mutex_unlock(&mutex_sum);

	pthread_exit((void *) 0);
} 
