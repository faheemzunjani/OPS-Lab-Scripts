#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define NUM_THREADS 32

struct thread_data {
	int thread_id;
	int priority_value;
	char message;
} t_d[NUM_THREADS];

void * print_priority(void *);

int main()
{
	pthread_t threads[1000];
	long priority_value;
	int status;
	long i;
	time_t t;
	char * message = "Faheem Hassan Zunjani - Meme God";

	srand((unsigned int) t);
	
	for (i = 0; i < NUM_THREADS; i++) {
		t_d[i].priority_value = rand() % NUM_THREADS;
		t_d[i].thread_id = i;
		t_d[i].message = message[i];

		status = pthread_create(&threads[i], NULL, print_priority, (void *) &t_d[i]);
		
		if (status) {
			printf("ERROR: Return code from pthread_create() is %d\n", status);
			exit(EXIT_FAILURE);
		}
	}

	pthread_exit(NULL);
				
	return 0;
}

void * print_priority(void * t_d)
{
	long priority_value;
	int i;
	struct thread_data * t_ptr;

	t_ptr = ((struct thread_data *)t_d);

	printf("Thread with id #%d and assigned priority %d and message %c\n", t_ptr->thread_id, t_ptr->priority_value, t_ptr->message);

	pthread_exit(NULL);
}
