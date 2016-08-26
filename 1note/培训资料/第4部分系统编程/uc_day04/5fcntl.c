#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main()
{
	int fd = open("a.txt",O_RDONLY|O_CREAT|O_APPEND,0666);
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}

	int fd2 = open("b.txt",O_RDWR);
	if(fd2<0)
	{
		perror("open");
		exit(-1);
	}

	//int fdn = fcntl(fd,F_DUPFD,4);
	//printf("fdn = %d\n",fdn);

	int flags = fcntl(fd,F_GETFL);
	printf("flags = %d\n",flags);

	if(flags&O_APPEND)
		printf("APPEND!\n");
	if(flags&O_CREAT)
		printf("CREAT!\n");
	if((flags&3)==O_RDWR)
		printf("O_RDWR!\n");//权限由低2位决定
	if((flags&3)==O_RDONLY)
		printf("O_RDONLY!\n");//权限由低2位决定
	

	return 0;
}
