#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("pid = %d.\n",getpid());
	printf("ppid = %d.\n",getppid());
	printf("uid = %d.\n",getuid());

	return 0;
}
