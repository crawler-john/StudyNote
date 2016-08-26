#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("%d begin.\n",getpid());
	pid_t pid = fork();
	printf("%d end.\n",pid);

	return 0;
}
