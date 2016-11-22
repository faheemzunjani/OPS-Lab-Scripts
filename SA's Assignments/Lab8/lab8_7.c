#include <stdio.h>

int main(int argc, char ** argv)
{
	FILE * fptr;
	char read_str[1000];

	fptr = fopen(argv[1], "r");

	fscanf(fptr, "%s", read_str);
	printf("%s", read_str);

	fclose(fptr);

	return 0;
}
