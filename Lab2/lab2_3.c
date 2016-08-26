#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int finddir(char *dir, int depth, char *file)
{
	char cwd[1024];
	static int status = 0;
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL) {
		fprintf(stderr,"Cannot open directory: %s\n", dir);
		return -1;
	}
	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			/* Found a directory, but ignore . and .. */
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			//printf("%*s%s/\n",depth,"",entry->d_name);
			finddir(entry->d_name,depth+4, file);
		}
		else{
			//printf("%*s%s\n",depth,"",entry->d_name);
			if(strcmp(entry->d_name, file)==0){
				if (getcwd(cwd, sizeof(cwd)) != NULL)
					printf("Found at: %s/%s\n",cwd,entry->d_name);
				status = 1;
			}
		}
	}
	chdir("..");
	closedir(dp);
	return status;
}

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("Invalid arguments!\n");
		printf("Usage: %s <filename> <directory>\n", argv[0]);
		exit(1);
	}
	printf("Searching %s in directory %s\n", argv[1], argv[2]);
	if(finddir(argv[2], 0, argv[1]) == 0){
		printf("%s not found!\n", argv[1]);
	}
	exit(0);
}