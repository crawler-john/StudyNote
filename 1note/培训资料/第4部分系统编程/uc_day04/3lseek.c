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
	char c;
	read(fd,&c,1);
	printf("%c\n",c);
	read(fd,&c,1);
	printf("%c\n",c);
	lseek(fd,2,SEEK_CUR);
	read(fd,&c,1);
	printf("%c\n",c);
	lseek(fd,0,SEEK_SET);//回到开头
	write(fd,"1",1);
	lseek(fd,3,SEEK_SET);
	write(fd,"2",1);
	lseek(fd,-2,SEEK_CUR);
	write(fd,"3",1);
	lseek(fd,-3,SEEK_END);
	write(fd,"4",1);

	close(fd);

	return 0;
}

