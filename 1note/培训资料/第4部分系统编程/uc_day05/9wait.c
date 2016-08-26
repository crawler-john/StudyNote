#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();
	if(!pid)//子进程
	{
		printf("子进程%d运行\n",getpid());
		sleep(1);
		printf("子进程%d结束\n",getpid());
		exit(100);
	}
	int status;
	pid_t wpid = wait(&status);
	printf("结束的子进程是%d\n",wpid);
	if(WIFEXITED(status))//判断正常结束
	{
		printf("正常结束,退出码%d\n",WEXITSTATUS(status));
	}

	printf("父进程结束!\n");

	return 0;
}

