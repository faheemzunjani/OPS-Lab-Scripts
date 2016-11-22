#include <stdio.h>

int main(int argc, char ** argv)
{
	FILE * fptr_src1;
	FILE * fptr_src2;
	FILE * fptr_dest;
	char read_char;

	fptr_src1 = fopen(argv[1], "r");
	fptr_src2 = fopen(argv[2], "r");
	fptr_dest = fopen(argv[3], "w");

	while (!feof(fptr_src1)) {
		fscanf(fptr_src1, "%c", &read_char);
		fprintf(fptr_dest, "%c", read_char);
	}	
	
	while (!feof(fptr_src2)) {
                fscanf(fptr_src2, "%c", &read_char);
                fprintf(fptr_dest, "%c", read_char);
        }	

	fclose(fptr_src1);
	fclose(fptr_src2);
	fclose(fptr_dest);

	return 0;
}
