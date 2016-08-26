#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("begin");
	pid_t pid = fork();
	if(!pid)
	{
		printf("hello\n");
		exit(0);
	}
	printf("welcome\n");

	return 0;
}
