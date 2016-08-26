#include <stdio.h>
#include <signal.h>

int main()
{
	sigset_t set;
	printf("size = %d\n",sizeof(set));
	printf("set = %d\n",set);
	sigemptyset(&set);//清空set
	printf("set = %d\n",set);
	sigaddset(&set,SIGINT);//2 00000010
	printf("set = %d\n",set);
	sigaddset(&set,SIGQUIT);//6 00000110
	printf("set = %d\n",set);
	sigaddset(&set,6);//38 00100110
	printf("set = %d\n",set);
	sigdelset(&set,6);//6 00000110
	printf("set = %d\n",set);
	if(sigismember(&set,3))
	{
		printf("信号集中有该信号\n");
	}
	else
	{
		printf("信号集中没有该信号\n");
	}

	return 0;
}

