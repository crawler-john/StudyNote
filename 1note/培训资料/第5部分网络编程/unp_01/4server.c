#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

int main()
{
	//1.创建socket描述符
	int fd = socket(PF_UNIX,SOCK_DGRAM,0);
	if(fd<0)
	{
		perror("socket");
		exit(-1);
	}
	printf("socket OK!\n");
	//2.构造通信地址
	struct sockaddr_un addr;//socket文件通信(本地通信)的地址
	addr.sun_family = AF_LOCAL;
	strcpy(addr.sun_path,"a.sock");
	//3.绑定socket描述符和通信地址
	int res = bind(fd,(struct sockaddr *)&addr,sizeof(addr));
	if(res<0)
	{
		perror("bind");
		close(fd);
		exit(-1);
	}
	printf("bind OK!\n");
	//4.通信
	/*
	char buf[100] = {};
	res = read(fd,buf,sizeof(buf));
	printf("读到%d字节，内容是%s\n",res,buf);
	*/
	char buf[100];
	int n = 0;
	while(n<10)
	{
		bzero(buf,sizeof(buf));
		read(fd,buf,sizeof(buf));
		printf("::%s\n",buf);
		n++;
	}
	//5.关闭socket描述符
	close(fd);
	unlink("a.sock");

	return 0;
}

