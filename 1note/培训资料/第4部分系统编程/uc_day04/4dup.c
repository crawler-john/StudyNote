#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int fd = open("a.txt",O_RDWR);
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}
	int fd2 = dup(fd);
	printf("fd = %d,fd2 = %d\n",fd,fd2);

	int fd3 = dup2(fd,5);
	printf("fd3 = %d\n",fd3);

	int fd4 = open("b.txt",O_RDWR|O_CREAT,0666);
	printf("fd4 = %d\n",fd4);

	int fd5 = dup2(fd,6);

	write(6,"hehe",4);

	close(fd);
		
	return 0;
}

