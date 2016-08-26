#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd = open("a.txt",O_RDWR|O_CREAT,0666);
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}

	pid_t pid = fork();
	if(!pid)//子进程
	{
		write(fd,"abc",3);//复制了文件描述符
		close(fd);//没有复制文件表
		exit(0);
	}
	write(fd,"123",3);
	close(fd);

	return 0;
}

