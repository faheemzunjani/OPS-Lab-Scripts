#include <stdio.h>

int main(int argc, char ** argv)
{
	FILE * fptr_src;
	FILE * fptr_dest;
	char read_char;

	fptr_src = fopen(argv[1], "r");
	fptr_dest = fopen(argv[2], "w");

	while (!feof(fptr_src)) {
		fscanf(fptr_src, "%c", &read_char);
		fprintf(fptr_dest, "%c", read_char);
	}	

	fclose(fptr_src);
	fclose(fptr_dest);

	return 0;
}
