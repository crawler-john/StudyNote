#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	umask(0111);

	int fd = open("a.txt",O_RDWR|O_CREAT|O_TRUNC,0644);//打开文件
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}
	
	int res = write(fd,"hello",5);//写文件
	printf("fd=%d,res=%d\n",fd,res);//3
	close(fd);

	fd = open("a.txt",O_RDONLY);//只读方式打开
	char buf[100] = {};
	res = read(fd,buf,sizeof(buf));
	printf("fd=%d\n",fd);//3 关闭后可重复使用

	printf("读到%d字节,内容为%s\n",res,buf);
	close(fd);

	return 0;
}


