#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int r_A;
int c_A;
int r_B;
int c_B;
int t_c;
int t_n;
double A[100][100];
double B[100][100];
double C[100][100];
int t_jobs[100];

void * threaded_multiply(void *);

int main(int argc, char ** argv) 
{
	FILE * fptr1;
	FILE * fptr2;
	pthread_t threads[100];
	int i; 
	int j;
	char readString[100];
	int t_status;
	int temp;
	int temp2;

	fptr1 = fopen(argv[2], "r");
	fptr2 = fopen(argv[4], "r");
	t_c = atoi(argv[6]);
	i = 0; 
	j = 0;

	/* Reading A and B from files */

	fscanf(fptr1, "%d %d", &r_A, &c_A);

	while (!feof(fptr1)) {
		fscanf(fptr1, "%s", readString);
		if (readString[0] == '#') {
			fscanf(fptr1, "%s", readString);
			fscanf(fptr1, "%s", readString);
			i = atoi(readString);
			j = 0;
		} else {
			A[i][j] = atof(readString);
			j++;
		}	
	}

	fscanf(fptr2, "%d %d", &r_B, &c_B);

	while (!feof(fptr2)) {  
		fscanf(fptr2, "%s", readString);
		if (readString[0] == '#') {
		    fscanf(fptr2, "%s", readString);
		    fscanf(fptr2, "%s", readString);
		    i = atoi(readString);
		    j = 0;
		} else {
		    B[i][j] = atof(readString);
		    j++;
		}
	}

	if (c_A != r_B) {
		printf("Incompatible matrices for matrix multiplication!\n");
		exit(EXIT_FAILURE);
	}

	/* Work division among the required threads */

	temp = r_A / t_c;
	temp2 = r_A % t_c;

	for (i = 0; i < t_c; i++) {
		t_jobs[i] = temp;
		if (temp2 > 0) {
			t_jobs[i]++;
			temp2--;
		}
	}

	/* Verifying work division */

	for (i = 0; i < t_c; i++) {
		printf("%d\n", t_jobs[i]);
	}

	/* Threaded matrix multiplication */

	for (i = 0; i < t_c; i++) {
		t_n = i;

		t_status = pthread_create(&threads[i], NULL, threaded_multiply, (void *)t_n);
		
		if (t_status) {
			printf("Error - pthread_create() return code: %d\n", t_status);
			exit(EXIT_FAILURE);
		}
	}

	/* Joining the threads */
	
	for (i = 0; i < t_c; i++) {
		pthread_join(threads[i], NULL);
	}
	
	/* Verifying A and B */

	for (i = 0; i < r_A; i++) {
		for (j = 0; j < c_A; j++) {
			printf("%lf ", A[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < r_A; i++) {
        for (j = 0; j < c_A; j++) {
            printf("%lf ", B[i][j]);
        }
        printf("\n");
    }
	

	/* Printing product matrix */

	printf("%d %d\n", r_A, c_B);
	for (i = 0; i < r_A; i++) {
		printf("# Row %d\n", i);
		for (j = 0; j < c_B; j++) {
			printf("%lf\n", C[i][j]);
		}
	}

	return 0;
}

void * threaded_multiply(void * arg_n)
{
	int t_n = (int) arg_n;
	int i;
	int j;
	int k;
	int temp;
	int temp2;
	double temp_sum;

	temp2 = 0;

	/* Determining start index of the current thread */

	if (t_n != 0) {
		for (temp = t_n - 1; temp >= 0; temp--) {
			temp2 += t_jobs[temp];
		}
	}

	/* Matrix multiplication */

	for (i = temp2; i < (temp2 + t_jobs[t_n]); i++) {
		for (j = 0; j < c_B; j++) {
			C[i][j] = 0;
			for (k = 0; k < c_A; k++) {
				C[i][j] += (A[i][k] * B[k][j]);
			}
		}
	}
}

