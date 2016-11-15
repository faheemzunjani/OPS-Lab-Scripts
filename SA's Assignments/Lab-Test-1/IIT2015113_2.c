#include <stdio.h>

struct process {
	int p_id;
	int at;
	int bt;
	int wt;
	int tat;
};

void insert(struct process queue[], struct process p, int * p_N);
struct process delete(struct process queue[], int * p_N);

int main()
{
	int N;
	struct process processes[100];
	int p_N;
	int i;
	int cur_time;
	int p_counter;
	struct process queue[100];
	struct process temp_p;
	float avg_wt;
	float avg_tat;
	float sum_wt = 0;
	float sum_tat = 0;

	scanf("%d", &N);

	for (i = 0; i < N; i++) {
		scanf("%d %d %d", &processes[i].p_id, &processes[i].at, &processes[i].bt);
		processes[i].wt = 0;
		processes[i].tat = 0;
	}

	p_N = 0;
	cur_time = -1;
	p_counter = 0;

	do {
		cur_time++;

		for (i = 0; i < N; i++) {
			if (processes[i].at == cur_time) {
				insert(queue, processes[i], &p_N);
				p_counter++;
			}
		}
		
		temp_p = delete(queue, &p_N);

		if (temp_p.bt == processes[temp_p.p_id].bt) {
			processes[temp_p.p_id].wt = cur_time - temp_p.at;
			temp_p.wt = cur_time - temp_p.at;
			temp_p.bt--;
			insert(queue, temp_p, &p_N);
		} else if (temp_p.bt == 0) {
			processes[temp_p.p_id].tat = cur_time - temp_p.at;
		} else {
			temp_p.bt--;
			insert(queue, temp_p, &p_N);
		}
	} while (p_N > 0 || p_counter < N);	

	sum_wt = 0;
	sum_tat = 0;

	for (i = 0; i < N; i++) {
		sum_wt += processes[i].wt;
		sum_tat += processes[i].tat;
	} 

	avg_wt = sum_wt / N;
	avg_tat = sum_tat / N;

	printf("ATT= %f\n", avg_tat);
	printf("AWT= %f\n", avg_wt);
	return 0;
}

void insert(struct process queue[], struct process p, int * p_N)
{
	queue[*p_N] = p;
	(*p_N)++;
}

struct process delete(struct process queue[], int * p_N)
{
	struct process max_p;
	int max_p_i;
	int i;

	max_p = queue[0];
	max_p_i = 0;

	for (i = *p_N - 1; i >= 1; i--) {
		if (queue[i].bt >= max_p.bt) {
			max_p = queue[i];
			max_p_i = i;
		}
	}

	for (i = max_p_i; i < (*p_N - 1); i++) {
		queue[i] = queue[i + 1];
	}

	(*p_N)--;

	return max_p;
}
