#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, char ** argv) 
{
	FILE * fptr1;
	FILE * fptr2;
	int thread_c;
	double A[100][100];
	double B[100][100];
	int i; 
	int j;
	int r_A;
	int c_A;
	int r_B;
	int c_B;
	char readString[100];

	fptr1 = fopen(argv[2], "r");
	fptr2 = fopen(argv[4], "r");
	thread_c = atoi(argv[6]);
	i = 0; 
	j = 0;
	
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
			printf("%lf\n");
		}
	}

	return 0;
}
