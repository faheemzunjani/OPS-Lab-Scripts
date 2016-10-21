#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1000

struct process {
	char name[100];
	int p_no;
	int arr_t;
	float bt;
	int priority;
	float tat;
	float wt;
	int in_queue;
	float vd;
};

void enqueue(struct process queue[], int * N, int * head, int * tail, struct process p, float et, float rrslice);
struct process dequeue(struct process queue[], int * N, int * head, int * tail);

int main(int argc, char ** argv)
{
	FILE *fptr;
	int ts;
	float avg_wt;
	float avg_tat;
	float rrslice;
	float var;
	struct process temp2_p;
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

	ts = atoi(argv[2]);
	rrslice = (float) ts;

	fptr = fopen(argv[1], "r");
	
	/* Input from file */	
	for (N = 0; !feof(fptr); N++) {	
		fscanf(fptr, "%s %d %f %d", processes[N].name, 
			&processes[N].arr_t, &processes[N].bt, &processes[N].priority);
		
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
		processes[i].vd = processes[i].arr_t + (rrslice * processes[i].priority);
	}	
	
	enqueue(queue, &q_N, &head, &tail, processes[0], et, rrslice);
	processes[0].in_queue = 1;

	/* Simulating Round Robin Algo */
	do {
		temp_p = dequeue(queue, &q_N, &head, &tail);
                p_no = temp_p.p_no;

		if (rrslice > processes[p_no + 1].arr_t) {
			temp_p.bt -= processes[p_no + 1].arr_t;
			et += processes[p_no + 1].arr_t;
		} else {
			temp_p.bt -= rrslice;
			et += rrslice;
		}

		/* Adding processes to ready queue by their arrival time */
		for (i = 0; i < N; i++) {
                       	if (processes[i].arr_t <= et && processes[i].in_queue != 1) {
                               	enqueue(queue, &q_N, &head, &tail, processes[i], et, rrslice);
                               	processes[i].in_queue = 1;                                	
                       	}
               	}
		
		enqueue(queue, &q_N, &head, &tail, temp_p, et, rrslice);
		temp2_p = dequeue(queue, &q_N, &head, &tail);
		
		if (temp_p.bt > 0) {
			et += temp_p.bt;
			cur_bt = temp_p.bt;
			temp_p.bt = 0;
			processes[p_no].wt = et - cur_bt;

			processes[p_no].tat = et;
		}			
	} while (q_N != 0);
		
	/* Displaying the output */
	printf("process_name turn_around_time total_wait_time\n");

	for (i = 0; i < N; i++) {
		printf("%s %.3f %.3f\n", processes[i].name, 
			processes[i].tat, processes[i].wt);
	}

	return 0;
}

void enqueue(struct process queue[], int * N, int * head, int * tail, struct process p, float et, float rrslice)
{
	p.vd = et + (rrslice * p.priority);

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
	int min_p;
	int i;
	struct process temp_p, temp2_p;
	if (*tail == 0) {
		temp_p = queue[0];
		*head = -1;
		*tail = -1;
		*N = 0;
	} else {
		min_p = *head;
		for (i = *head; i <= *tail; i++) {
			if (queue[i].vd < queue[min_p].vd) {
				min_p = i;
			}
		}

		temp_p = queue[min_p];

		for (i = min_p; i < *tail; i++) {
			queue[i] = queue[i + 1];
		}
		(*N)--;
		(*tail)--;
	}

	return temp_p;
}
