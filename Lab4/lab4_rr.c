#include <stdio.h>
#include <math.h>
#define MAX_SIZE 1000

struct process {
	char name[100];
	int p_no;
	int arr_t;
	float bt;
	float io_et;
	float io_wt;
	int priority;
	float tat;
	float wt;
	int in_queue;
};

void enqueue(struct process queue[], int * N, int * head, int * tail, struct process p);
struct process dequeue(struct process queue[], int * N, int * head, int * tail);

int main(int argc, char ** argv)
{
	FILE *fptr;
	float avg_wt;
	float avg_tat;
	float sd_tat;
	float ts;
	float var;
	float sum_var;
	float temp_sum;
	float et;
	float cur_bt;
	int i;
	int j;
	int N;
	int p_no;
	int head;
	int tail;
	int q_N;
	char filename[100];
	struct process processes[MAX_SIZE];
	struct process queue[MAX_SIZE];
	struct process temp_p;

	avg_wt = 0.0;
	avg_tat = 0.0;
	head = -1;
	tail = -1;
	q_N = 0;

	printf("The name of the file to be read: ");
	scanf("%s", filename);
	
	printf("The time slice: ");
	scanf("%f", &ts);

	fptr = fopen(filename, "r");
	
	/* Input from file */	
	for (N = 0; !feof(fptr); N++) {	
		fscanf(fptr, "%s %d %f %f %f %d", processes[N].name, 
			&processes[N].arr_t, &processes[N].bt, &processes[N].io_et, 
			&processes[N].io_wt, &processes[N].priority);
		
		processes[N].p_no = N;
		processes[N].wt = 0;
		processes[N].tat = 0;
		processes[N].in_queue = 0;

		if (processes[N].name[0] == 'x') {
			break;
		}
	}

	fclose(fptr);
	
	et = 0;
	temp_sum = 0;

	/* Computing arrival times wrt to P1*/
	for (i = 0; i < N; i++) {
		temp_sum += processes[i].arr_t;
		processes[i].arr_t = temp_sum;	
	}	
	
	enqueue(queue, &q_N, &head, &tail, processes[0]);
	processes[0].in_queue = 1;

	/* Simulating Round Robin Algo */
	do {
		temp_p = dequeue(queue, &q_N, &head, &tail);
                p_no = temp_p.p_no;

		if (temp_p.bt > ts) {
			temp_p.bt -= ts;
			et += ts;
			
			/* Adding processes to ready queue by their arrival time */
			for (i = 0; i < N; i++) {
                        	if (processes[i].arr_t <= et && processes[i].in_queue != 1) {
                                	enqueue(queue, &q_N, &head, &tail, processes[i]);
                                	processes[i].in_queue = 1;                                	
                        	}
                	}

			enqueue(queue, &q_N, &head, &tail, temp_p);
		} else if (temp_p.bt > 0) {
			et += temp_p.bt;
			cur_bt = temp_p.bt;
			temp_p.bt = 0;
			processes[p_no].wt = et - cur_bt;
			avg_wt += processes[p_no].wt;
			processes[p_no].tat = et;
			avg_tat += processes[p_no].tat;
		}			
	} while (q_N != 0);
		
	avg_tat /= (float) (N);
	avg_wt /= (float) (N);
	sum_var = 0;

	/* Computing standard deviation of turn around times times */
	for (i = 0; i < N; i++) {
		var = pow((processes[i].tat - avg_tat), 2);
		sum_var += var;
	}

	sd_tat = pow((sum_var / (float) N), 0.5);

	/* Displaying the output */
	printf("\tprocess name \t turn around time \t total wait time\n");

	for (i = 0; i < N; i++) {
		printf("\t      %s \t      %f \t      %f \n", processes[i].name, 
			processes[i].tat, processes[i].wt);
	}

	printf("The average time for processes to complete was %f \n", avg_tat);
	printf("The standard deviation for the average process completion time was %f \n", sd_tat);	

	return 0;
}

void enqueue(struct process queue[], int * N, int * head, int * tail, struct process p)
{
	if (*tail == -1) {
		*head = 0;
		*tail = 0;
		*N = 1;
		queue[0] = p;
	} else if (*tail == MAX_SIZE - 1 && *head == 0) {
		printf("Queue is full. Aborting!\n");
	} else {
		(*tail)++;
		(*N)++;
		queue[*tail] = p;
	}
}

struct process dequeue(struct process queue[], int * N, int * head, int * tail) 
{
	struct process temp_p;
	int i;

	if (*tail == 0) {
		temp_p = queue[0];
		*head = -1;
		*tail = -1;
		*N = 0;
	} else {
		temp_p = queue[*head];
		
		for (i = *head; i < *tail; i++) {
			queue[i] = queue[i + 1];
		}
		(*N)--;
		(*tail)--;
	}

	return temp_p;
}
