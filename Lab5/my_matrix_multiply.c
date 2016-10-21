#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arg {
	int r_A;
	int c_A;
	int r_B;
	int c_B;
	int t_c;
	int t_n;
};

double A[100][100];
double B[100][100];
double C[100][100];

void * threaded_multiply(void *);

int main(int argc, char ** argv) 
{
	FILE * fptr1;
	FILE * fptr2;
	int thread_c;
	pthread_t threads[100];
	int i; 
	int j;
	int r_A;
	int c_A;
	int r_B;
	int c_B;
	char readString[100];
	struct arg arg_t;
	struct arg * arg_ptr = NULL;
	int t_status;

	fptr1 = fopen(argv[2], "r");
	fptr2 = fopen(argv[4], "r");
	thread_c = atoi(argv[6]);
	i = 0; 
	j = 0;
	arg_t.r_A = r_A;
	arg_t.r_B = r_B;
	arg_t.c_A = c_A;
        arg_t.c_B = c_B;
	arg_t.t_c = thread_c;
	arg_ptr = &arg_t;

	/* Reading A and B from files */
	fscanf(fptr1, "%d %d", &r_A, &c_A);
	fscanf(fptr2, "%d %d", &r_B, &c_B);

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
	
	/* Threaded Matrix Multiplication */
	for (i = 0; i < thread_c; i++) {
		arg_t.t_n = i;
		t_status = pthread_create(&threads[i], NULL, threaded_multiply, (void *) arg_ptr);
		
		if (t_status) {
			printf("Error - pthread_create() return code: %d\n", t_status);
			exit(EXIT_FAILURE);
		}
	}

	for (i = 0; i < thread_c; i++) {
		pthread_join(threads[i], NULL);
	}

	/* Verifying A and B */
	/* 
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
	*/

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

void * threaded_multiply(void * arg_x)
{
	struct arg * arg_ptr = (struct arg *) arg_x;
	int i;
	int j;
	int k;

	for (i = (arg_ptr->t_c * arg_ptr->t_n); i < ((arg_ptr->t_c * arg_ptr->t_n) + arg_ptr->t_c); i++) {
		for (j = 0; j < arg_ptr->c_B; j++) {
			C[i][j] = 0;
			for (k = 0; k < arg_ptr->r_B; k++) {
				C[i][j] += (A[i][k] * B[k][j]);
			}
		}
	}
		
}
