#include <stdio.h>

int main(int argc, char ** argc)
{
	int status;

	status = remove(argc[1]);

	if (status == 0) {
		printf("%s deleted successfully!\n", argc[1]);
	} else {
		printf("Error: Unable to delete %s!\n", argc[1]);
	}

	return 0;
}