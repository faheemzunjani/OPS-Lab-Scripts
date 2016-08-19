#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	int fd;
	char * cmd[] = {"ls", "-l", NULL};
	pid_t child;
	char * buf = malloc ( sizeof )

	if (!strcmp(argv[0], "cat")) {
		/* Code to implement cat */
		fd = open(argv[0], O_RDONLY);
		
		
	} else if (!strcmp(argv[0], "mv")) {
		/* Code to implement mv */
	} else if (!strcmp(argv[0], "ls")){
		/* Code to implement ls */
		child = fork();
		if (child < 0) {
			printf("Error creating child process\n");
			return 1;
		} else if (child == 0) {
			execv("/bin/ls", cmd);
			exit(20);
		} else {
			child = wait(0);
			return 1;
		}		
	} else {
		printf("Command not found\n");
	}

	return 1;
}
