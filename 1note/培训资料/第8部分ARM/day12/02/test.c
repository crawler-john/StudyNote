#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

char buf[10];

int main()
{
	int fd = open("/dev/cdd",O_RDWR);
	if(fd<0)
	{
		printf("open failed!\n");
		return -1;
	}

	printf("open successed!fd = %d\n",fd);
	read(fd,buf,1);
	write(fd,buf,1);
	ioctl(fd,1,1);
	
	close(fd);
	return 0;
}
