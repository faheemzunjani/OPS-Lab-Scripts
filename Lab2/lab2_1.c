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
	int fd1;
	int fd2;
	int dataSize;
	char * cmd[] = {"ls", "-l", NULL};
	char buf[2];
	pid_t child;

	if (!strcmp(argv[1], "cat")) {
		/* Code to implement cat */

                fd = open(argv[2], O_RDONLY);
		
		do {
			dataSize = read(fd, buf, 1);
			printf("%c", buf[0]);
		} while (dataSize != 0);

		close(fd);
                exit(20);
	} else if (!strcmp(argv[1], "mv")) {
		/* Code to implement mv */
		
		fd1 = open(argv[2], O_RDWR, 0777);
		fd2 = open(argv[3], O_RDWR | O_CREAT, 0777);

		do {
			dataSize = read(fd1, buf, 1);
			printf("%c", buf[0]);
			write(fd2, buf, 1);
		} while (dataSize != 0);

		close(fd1);
		unlink(argv[2]);
		close(fd2);
		exit(20);
	} else if (!strcmp(argv[1], "ls")){
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
