#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char ** argv)
{
    FILE * fptr;
    struct stat status;

    fptr = fopen(argv[1], "r");
    
    fstat(fileno(fptr), &status);
    
    printf("Last time of modification : %s", ctime(&status.st_ctime));
    
    return 0;
}