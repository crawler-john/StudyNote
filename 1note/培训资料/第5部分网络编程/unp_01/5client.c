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
	//3.连接socket描述符和服务器通信地址
	int res = connect(fd,(struct sockaddr *)&addr,sizeof(addr));
	if(res<0)
	{
		perror("connect");
		close(fd);
		exit(-1);
	}
	printf("connect OK!\n");
	//4.通信
	//write(fd,"hello",5);
	int n = 0;
	while(n<10)
	{
		write(fd,"靓仔!",sizeof("靓仔!"));
		sleep(1);
		n++;
	}
	//5.关闭socket描述符
	close(fd);

	return 0;
}

