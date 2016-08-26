#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void fa(int signo)//系统会把信号值传递过来
{
	printf("捕获了信号%d\n",signo);
}

int main()
{
	printf("pid = %d\n",getpid());
	signal(SIGINT,SIG_IGN);//忽略信号2
	if(signal(SIGQUIT,fa)==SIG_ERR)//自定义处理方式
	{
		printf("信号处理登记出错\n");
	}
	signal(SIGKILL,fa);

	while(1);
}

