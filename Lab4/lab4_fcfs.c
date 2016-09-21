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
	int i;
	int j;
	int N;
	char filename[100];
	struct process processes[100];
	
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

	/* Computing wait times */
	for (i = 0; i < N; i++) {
		processes[i].wt = 0;

		for (j = 0; j < i; j++) {
			processes[i].wt += processes[j].bt;
		}

		processes[i].wt -= processes[i].arr_t;
		avg_wt += processes[i].wt;
	}
	
	/* Computing turn around times */ 
	for (i = 0; i < N; i++) {
		processes[i].tat = processes[i].wt + processes[i].bt;
		avg_tat += processes[i].tat;
	}
	
	avg_tat /= (float) (N);
	avg_wt /= (float) (N);
	sum_var = 0;

	/* Computing standard deviation of turn around times times */
	for (i = 0; i < N; i++) {
		var = pow((processes[i].tat - avg_tat), 2);
		sum_var += var;
	}

	sd_tat = pow((sum_var / (float) N), (1 / 2));

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
