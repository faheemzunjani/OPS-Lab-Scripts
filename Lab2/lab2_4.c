#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <ftw.h>
#include <unistd.h>
#include <stdlib.h>

int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    int rv = remove(fpath);

    if (rv)
        perror(fpath);

    return rv;
}

int rmrf(char *path)
{
    return nftw(path, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("Invalid arguments!\n");
		printf("Usage: %s <dir_name>\n", argv[0]);
		exit(1);
	}
	if(rmrf(argv[1]) == 0)
		printf( "Succesfully deleted %s!\n", argv[1]);
	else
		printf("Error deleting %s!\n", argv[1]);
	return 0;
}