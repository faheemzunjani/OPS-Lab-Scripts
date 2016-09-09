#include <stdio.h>

int main(int argc, char ** argv)
{
	FILE *fptr;
	int pid[1000];
	float bt[1000];
	float wt[1000];
	float tat[1000];
	float avg_wt;
	float avg_tat;
	int i;
	int j;
	int N;
	
	avg_wt = 0.0;
	avg_tat = 0.0;

	fptr = fopen(argv[1], "r");

	for (N = 0; !feof(fptr); N++) {	
		fscanf(fptr, "%d %f", &pid[N], &bt[N]);
	}
	
	for (i = 0; i < N - 1; i++) {
		wt[i] = 0;
		for (j = 0; j < i; j++) {
			wt[i] += bt[j];
			avg_wt += wt[i];
		}
	}

	for (i = 0; i < N - 1; i++) {
		tat[i] = wt[i] + bt[i];
		avg_tat += tat[i];
	}
	
	avg_tat /= (float)(N);
	avg_wt /= (float)(N);

	printf("PID \t Burst Time \t Waiting Time \t Turn Around Time\n");

	for (i = 0; i < N - 1; i++) {
		printf("%d \t %f \t %f \t %f\n", pid[i], bt[i], wt[i], tat[i]);
	}
	
	close(fptr);

	return 0;
}
