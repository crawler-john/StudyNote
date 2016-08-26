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
	int fd = socket(PF_INET,SOCK_STREAM,0);
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
	char buf[100] = {};
	char rcv[100] = {};
	while(1)
	{
		printf("请输入聊天内容:");
		scanf("%s",buf);//清buf
		printf("buf:%s\n",buf);
		write(fd,buf,sizeof(buf));
		if(strcmp(buf,"bye")==0)
			break;
		read(fd,rcv,sizeof(rcv));
		printf("%s\n",rcv);
		memset(rcv,0,strlen(rcv));//请rcv
	}
	//5.关闭socket描述符
	close(fd);

	return 0;
}

