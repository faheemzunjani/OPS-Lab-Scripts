#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define TCOUNT 10
#define NUM_THREADS 2
#define COUNT_LIMIT 12

pthread_mutex_t count_mutex;
pthread_cond_t count_th_cv;
long int count;
long int sum;
pthread_t threads[NUM_THREADS] = {0, 1};

void * inc_fun(void *);
void * dec_fun(void *);

int main()
{
	int status;
	long int i;
	long int t_no;
	pthread_attr_t attr;

	pthread_mutex_init(&count_mutex, NULL);
	pthread_cond_init(&count_th_cv, NULL);

	status = pthread_create(&threads[0], &attr, inc_fun, (void *) t_no);
	status = pthread_create(&threads[1], &attr, dec_fun, (void *) t_no);
	if (status) {
			printf("ERROR: Return code from pthread_create() is %d\n", status);
			exit(EXIT_FAILURE);
		}
	}

	pthread_mutex_destroy(&mutex_sum);
	pthread_cond_destroy(&count_mutex);
	pthread_exit(NULL);
				
	return 0;
}

void * dec_fun(void * t)
{
	long int * v;
	long int i;
	long int temp;
	long int partial_sum;
		
	v = (long int *) t;
	
	while (1) {
		if (*v) {
			sleep(1);
		} else {
			pthread_mutex_lock(&count_mutex);
			printf("Locked!\n");
			--(*v);
			printf("Decrementing\n");
			pthread_mutex_unlock(&count_mutex);
			printf("Unlocked!\n");
		}
	}

	pthread_exit((void *) 0);
}

void * inc_fun(void * t)
{
        long int * v;
        long int i;
        long int temp;
        long int partial_sum;

        v = (long int *) t;

        while (1) {
                if (*v) {
                        sleep(1);
                } else {
                        pthread_mutex_lock(&count_mutex);
                        printf("Locked!\n");
                        ++(*v);
                        printf("Incrementing\n");
                        pthread_mutex_unlock(&count_mutex);
                        printf("Unlocked!\n");
                }
        }

        pthread_exit((void *) 0);
}
