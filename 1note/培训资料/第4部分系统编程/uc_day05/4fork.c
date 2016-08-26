#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int i1 = 10;//全局段
int i2;//bss段

int main()
{
	int i3 = 10;//栈
	int *pi = malloc(4);//堆
	pid_t pid = fork();
	if(!pid)//子进程分支
	{
		i1 = 20;i2 = 20;i3 = 20;*pi = 20;
		printf("c:i1=%d,i2=%d,i3=%d,*pi=%d.\n",
				i1,i2,i3,*pi);
		printf("c:%p,%p,%p,%p.\n",&i1,&i2,&i3,pi);
		exit(0);//结束子进程
	}
	sleep(1);
	printf("f:i1=%d,i2=%d,i3=%d,*pi=%d.\n",
			i1,i2,i3,*pi);
	printf("f:%p,%p,%p,%p.\n",&i1,&i2,&i3,pi);

	return 0;
}

