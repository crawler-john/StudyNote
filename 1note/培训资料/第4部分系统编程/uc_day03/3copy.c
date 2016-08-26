#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int fdr = open("a.txt",O_RDONLY);
	if(fdr<0)perror("open a"),exit(-1);

	int fdw = open("b.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
	if(fdw<0)perror("open b"),exit(-1);

	char buf[4096] = {};


	while(1)
	{
		int res = read(fdr,buf,sizeof(buf));
		if(res<0)
		{
			perror("read");
			break;
		}
		if(res==0)
			break;
		write(fdw,buf,res);
	}

	/*
	int res = 0;
	while(res=read(fdr,buf,sizeof(buf)),res>0)
	{
		write(fdw,buf,res);
	}
	*/

	close(fdr);
	close(fdw);

	return 0;
}


