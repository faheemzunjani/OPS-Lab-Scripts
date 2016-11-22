#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
	int fd;
	long long int size;

	fd = open(argv[1], O_RDONLY);

	size = lseek(fd, (size_t)0, SEEK_END);

	printf("Size of %s : %lld\n", argv[1], size);

	close(fd);

	return 1;
}

