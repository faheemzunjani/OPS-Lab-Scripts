#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char ** argv)
{
    FILE * fptr;
    struct stat status;

    stat(argv[1], &status);

    if (status.st_mode & S_IFDIR) {
        printf("It is directory.\n");
    } else if (status.st_mode & S_IFCHR) {
        printf("It is character file.\n");
    } else if (status.st_mode & S_IFREG) {
        printf("It is regular file.\n");
    }

    return 0;
}