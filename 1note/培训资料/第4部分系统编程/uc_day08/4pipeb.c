#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd = open("a.pipe",O_WRONLY);
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}

	int i;
	for(i=0;i<100;i++)
	{
		write(fd,&i,sizeof(int));
		usleep(100000);//0.1s
	}
	printf("write OK!\n");
	close(fd);

	return 0;
}

