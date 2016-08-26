#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("a.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}

	struct flock lock;
	lock.l_type = F_WRLCK;//写锁
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;//从开头开始锁
	lock.l_len = 15;//锁15个字节
	lock.l_pid = -1;//上锁时没用,-1防止误解

	int res = fcntl(fd,F_SETLK,&lock);
	if(res==-1)
		printf("上锁失败!\n");
	else
		printf("上锁成功!\n");

	close(fd);

	return 0;
}
