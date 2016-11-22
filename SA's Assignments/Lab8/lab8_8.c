#include <stdio.h>

int main(int argc, char ** argv)
{
	FILE * fptr;
	int A[100];
	int i;
	int N;

	scanf("%d", &N);

	for (i = 0; i < N; i++) {
		scanf("%d", &A[i]);
	}

	fptr = fopen(argv[1], "w");

	for (i = 0; i < N; i++) {
		fprintf(fptr, "%d ", A[i]);
	}
	fprintf(fptr, "\n");

	fclose(fptr);

	return 0;
}
