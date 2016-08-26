#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid = vfork();
	if(!pid)//子进程
	{
		sleep(1);
		printf("子进程结束!\n");
		exit(0);//确保子进程退出
	}

	printf("父进程结束!\n");
}
