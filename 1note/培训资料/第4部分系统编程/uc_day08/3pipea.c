#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	//创建管道文件
	int r = mkfifo("a.pipe",0644);
	if(r<0)
	{
		printf("mkfifo:%m\n");
		exit(-1);
	}
	//打开管道文件
	int fd = open("a.pipe",O_RDONLY);
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}

	//循环从管道文件读取数据
	for(;;)
	{
		int x;
		int res = read(fd,&x,sizeof(int));
		if(res<=0)
			break;
		printf("x = %d\n",x);
	}
	close(fd);

	unlink("a.pipe");//删除管道文件
	return 0;
}

