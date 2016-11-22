#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char ** argv)
{
    FILE * fptr;
    struct stat status;
    
    stat(argv[1], &status);
    
    printf("You have permission to: ");

    if (status.st_mode & S_IREAD) {
		printf("Read ");
    }

    if (status.st_mode & S_IWRITE) {
		printf("Write ");
    } 

    if (status.st_mode & S_IEXEC) {
    	printf("Execute ");
    }
    printf("\n");

	return 0;
}