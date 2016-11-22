#include <stdio.h>

int main(int argc, char ** argv)
{
	FILE * fptr;

	fptr = fopen(argv[1], "w");

	fprintf(fptr, "%s", argv[2]);

	fclose(fptr);

	return 0;
}
