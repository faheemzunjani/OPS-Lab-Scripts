#include<stdio.h>
#include<unistd.h>
int main()
{
	int pid=fork();	
	int a=5;
	if(pid > 0)
		printf("%p parent\n",&a);
	else
		printf("%p child\n",&a);

	while(1);

	return 0;
}
