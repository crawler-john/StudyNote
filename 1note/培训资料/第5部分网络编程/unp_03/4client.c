#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
	//1.创建socket描述符
	int fd = socket(PF_INET,SOCK_DGRAM,0);
	if(fd<0)
	{
		perror("socket");
		exit(-1);
	}
	printf("socket OK!\n");
	//2.构造通信地址
	struct sockaddr_in addr;//socket文件通信(本地通信)的地址
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);//服务器的端口
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//服务器ip地址
	//UDP是基于无连接的协议，理应不connect就能发送
	//4.通信
	//write(fd,"hello",5);
	int res = sendto(fd,"hello",5,0,(struct sockaddr *)&addr,sizeof(addr));
	if(res<0)
	{
		perror("sendto");
		exit(-1);
	}
	char buf[100] = {};
	read(fd,buf,sizeof(buf));
	printf("%s\n",buf);
	//5.关闭socket描述符
	close(fd);

	return 0;
}

