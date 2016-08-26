#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void fa(int signo)
{
	printf("捕获了信号%d\n",signo);
	printf("起来嗨！\n");
	alarm(1);
}

int main()
{
	signal(SIGALRM,fa);
	int res = alarm(3);
	printf("res = %d\n",res);
	sleep(1);
	res = alarm(4);//返回之前剩余的秒数
	printf("res = %d\n",res);

	sleep(2);
	alarm(0);//取消发送闹钟信号

	while(1);
}
