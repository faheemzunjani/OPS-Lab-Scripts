#include <stdio.h>
#include <math.h>

struct process {
	char name[100];
	int arr_t;
	float bt;
	float io_et;
	float io_wt;
	int priority;
	float tat;
	float wt;
	int in_queue;
	int p_no;
};

int main(int argc, char ** argv)
{
	FILE *fptr;
	float avg_wt;
	float avg_tat;
	float sd_tat;
	float var;
	float sum_var;
	float temp_sum;
	float et;
	int i;
	int j;
	int N;
	int q_N;
	int min_p;
	int prev_min_p;
	char filename[100];
	struct process processes[100];
	struct process queue[100];
	
	avg_wt = 0.0;
	avg_tat = 0.0;

	printf("The name of the file to be read: ");
	scanf("%s", filename);

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
	
	temp_sum = 0;

	/* Computing arrival times wrt to P1*/
	for (i = 0; i < N; i++) {
		temp_sum += processes[i].arr_t;
		processes[i].arr_t = temp_sum;
	}	

	q_N = 1;
	et = 0;
	
	queue[0] = processes[0];
	processes[0].in_queue = 1;
	min_p = 0;

	while (q_N != 0) {
		prev_min_p = min_p;

		/* Finding process with min burst time */
		while (prev_min_p == min_p && queue[min_p].bt != 0) {
			queue[min_p].bt--;
			et++;
			processes[min_p].wt--;


			/* Adding processes to ready queue by their arrival time */
			for (i = 0; i < N; i++) {
            	if (processes[i].arr_t <= et && processes[i].in_queue != 1) {
                	queue[q_N] = processes[i];
                	processes[i].in_queue = 1;
                	q_N++;                                	
            	}
        	}

        	/* Finding process with min burst time */
			for (i = 0; i < q_N; i++) {
				if (queue[i].bt < queue[min_p].bt) {
					min_p = i;
				}
			}
		}

		processes[prev_min_p].wt += et;

        if (queue[min_p].bt == 0) {
        	processes[min_p].wt -= processes[min_p].arr_t;
        	processes[min_p].tat = et;

        	avg_wt += processes[min_p].wt;
        	avg_tat += processes[min_p].tat;

        	for (i = min_p; i < q_N; i++) {
				queue[i] = queue[i + 1];
			}

			q_N--;
        }
	}

	
	
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
