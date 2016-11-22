#include <stdio.h>

int main()
{
	FILE * fptr_src;
	char read_char;

	fptr_src = fopen("lab8_5.c", "r");

	while (!feof(fptr_src)) {
		fscanf(fptr_src, "%c", &read_char);
		printf("%c", read_char);
	}	

	fclose(fptr_src);

	return 0;
}
