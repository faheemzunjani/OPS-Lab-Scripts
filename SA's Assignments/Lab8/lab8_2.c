#include <stdio.h>

int main(int argc, char ** argv)
{
	int status;

	status = remove(argv[1]);

	if (status == 0) {
		printf("%s deleted successfully!\n", argv[1]);
	} else {
		printf("Error: Unable to delete %s!\n", argv[1]);
	}

	return 0;
}