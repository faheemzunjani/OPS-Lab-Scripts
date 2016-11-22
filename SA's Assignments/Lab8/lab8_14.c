#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char ** argv)
{
    FILE * fptr;
    struct stat status;

    fptr = fopen(argv[1], "r");

    fstat(fileno(fptr), &status);
    
    printf("Size of file: %lld\n", status.st_size);
    printf("Drive name: %c\n", 65 + status.st_dev);
    
    return 0;
}
