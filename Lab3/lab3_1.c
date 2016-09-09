#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	int pid,status;
	pid= fork();
	if(pid>0)
	{
		pid = wait(&status);
		printf("in parent process , child pid = %d and state = %d   %0x",pid,status,status);

	}
	else
	{

	}

	return 0;
}
