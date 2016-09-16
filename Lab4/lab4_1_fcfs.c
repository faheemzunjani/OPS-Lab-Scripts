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
	float sd_wt;
	float var;
	float sum_var;
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
	for (N = 0; !feof(fptr) && processes[N].name[0] != 'x'; N++) {	
		fscanf(fptr, "%s %d %f %f %f %d", processes[N].name, 
			&processes[N].arr_t, &processes[N].bt, &processes[N].io_et, 
			&processes[N].io_wt, &processes[N].priority);
		if (processes[N].name[0] == 'x') {
			break;
		}
	}
	fclose(fptr);
	
	/* Computing wait times */
	for (i = 0; i < N; i++) {
		processes[i].wt = 0;
		for (j = 0; j < i; j++) {
			processes[i].wt += processes[j].bt;
			avg_wt += processes[i].wt;
		}
	}
	
	/* Computing turn around times */ 
	for (i = 0; i < N; i++) {
		processes[i].tat = processes[i].wt + processes[i].bt;
		avg_tat += processes[i].tat;
	}
	
	avg_tat /= (float) (N + 1);
	avg_wt /= (float) (N + 1);
	sum_var = 0;

	/* Computing standard deviation of wait times */
	for (i = 0; i < N; i++) {
		var = pow((processes[i].wt - avg_wt), 2);
		sum_var += var;
	}

	sd_wt = pow((sum_var / (float) N), (1 / 2));

	/* Displaying the output */
	printf("\tprocess name \t turn around time \t total wait time\n");

	for (i = 0; i < N; i++) {
		printf("\t      %s \t      %f \t      %f \n", processes[i].name, 
			processes[i].tat, processes[i].wt);
	}

	printf("The average time for processes to complete was %f \n", avg_wt);
	printf("The standard deviation for the average process completion time was %f \n", sd_wt);	

	return 0;
}
