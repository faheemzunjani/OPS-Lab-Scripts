#include <stdio.h>
#include <unistd.h>
int main()
{
	int a,b;
	char ch;
	printf("Enter values and sign\n");
	scanf("%d%d%c%c",&a,&b,&ch,&ch);
	int pid=fork();
	int status;
	if(pid>0)
	{
		wait(&status);
		printf("answer = %d\n",status);

	}
	else
	{
		execl("/home/debadutt
	


	}
	return 0;
}
