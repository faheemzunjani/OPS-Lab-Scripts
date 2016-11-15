#include <stdio.h>

struct process {
	int p_id;
	int at;
	int bt;
	int priority;
	int wt;
	int tat;
};

/* Min-Priority Queue Operations */
void insert(struct process processes[], struct process p, int * p_N);
struct process delete(struct process processes[], int * p_N);

int main()
{
	struct process processes[100];
	struct process min_p;
	struct process temp_process;
	struct process c_process;
	struct process p_queue[100];
	struct process c_queue[100];
	int p_N;
	int c_N;
	int min_p_i;
	int i;
	int j;
	int N;
	int p_counter;
	int cur_time;
	
	printf("Enter the number of processes -- ");
	scanf("%d", &N);

	p_N = 0;
	c_N = 0;

	for (i = 0; i < N; i++) {
		processes[i].p_id = i;
		printf("Enter Arrival Time for Process %d -- ", i);
		scanf("%d", &processes[i].at);
		printf("Enter Burst Time for Process %d -- ", i);
		scanf("%d", &processes[i].bt);
		printf("Enter Priority for Process %d -- ", i);
                scanf("%d", &processes[i].priority);
		processes[i].wt = 0;
		processes[i].tat = 0;
	}

	/* Simulating Preemptive Priority Scheduling Algorithm */
	
	cur_time = -1;
	p_counter = 0;
	
	do {
		cur_time++;

		if (processes[p_counter].at == cur_time && p_counter < N) {
			insert(p_queue, processes[p_counter], &p_N);
			p_counter++;
		}

		temp_process = delete(p_queue, &p_N);

		if (temp_process.bt == processes[temp_process.p_id].bt) {
			temp_process.wt = cur_time - temp_process.at;
			temp_process.bt--;
			insert(p_queue, temp_process, &p_N);
		} else {
			temp_process.bt--;

			if (temp_process.bt == 0) {
				temp_process.tat = cur_time - temp_process.at;
				insert(c_queue, temp_process, &c_N);
			} else {
				insert(p_queue, temp_process, &p_N);
			}
		}	
	} while (p_N > 0 || p_counter < N);

	/* Printing the output */

	printf("PROCESS BURST TIME WAITING TIME TURNAROUND TIME\n");

	for (i = 0; i < c_N; i++) {
		printf("%d\t  %d\t\t%d\t\t%d\n", c_queue[i].p_id, processes[c_queue[i].p_id].bt, c_queue[i].wt, c_queue[i].tat);
	}		

	return 0;
}

void insert(struct process queue[], struct process p, int * p_N)
{
	queue[*p_N] = p;
	(*p_N)++;
}

struct process delete(struct process queue[], int * p_N)
{
	int i;
	int j;
	int min_p_i;
	struct process min_p;
	
	min_p = queue[0];
	min_p_i = 0;
	
	if (*p_N > 0) { 
        	for (i = 0; i < *p_N; i++) {
        		if (queue[i].priority < min_p.priority) {
                		min_p = queue[j];
                        	min_p_i = j;
       	        	}
       		}

		for (i = min_p_i; i < *p_N; i++) {
			queue[i] = queue[i + 1];
		}
		
		(*p_N)--;
	}

	return min_p;
}
