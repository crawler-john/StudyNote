#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid = vfork();
	if(!pid)
	{
		printf("cpid = %d\n",getpid());
		execl("./b.out","b.out",NULL);
		exit(0);//vfork()一定要用exit退出
	}

	sleep(1);
	int i;
	for(i=0;i<50;i++)
		printf("p:%d\n",i);

	return 0;
}


