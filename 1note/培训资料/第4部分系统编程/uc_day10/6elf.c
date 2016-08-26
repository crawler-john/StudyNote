#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <pwd.h>

int term = 0;
void func(int sig)
{
	term = 1;
}

int main()
{
	//创建子进程，让父进程结束
	if(fork()!=0)
		return 0;
	signal(SIGQUIT,func);
	printf("cid = %d\n",getpid());

	int i;
	//关闭从父进程继承的文件描述符
	for(i=0;i<256;i++)
		close(i);
	//成立自己的进程组
	setsid();
	//修改从父进程继承的权限屏蔽字
	umask(0000);
	//设置当前工作目录
	chdir(getpwuid(getuid())->pw_dir);//getenv("HOME")|getpwnam
	//执行真正的服务工作
	char c = 'A';
	for(;term==0;)
	{
		int fd = open("abc",O_WRONLY|O_CREAT,0644);
		if(fd<0)
			continue;
		write(fd,&c,1);
		close(fd);
		if(++c>'Z')
			c='A';
		sleep(1);
	}

	unlink("abc");
	return 0;
}
