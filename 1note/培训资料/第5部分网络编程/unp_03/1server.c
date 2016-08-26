#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>

int fd;

void fa(int signo)
{
	close(fd);
	printf("服务器关闭\n");
	exit(0);
}

int main()
{
	printf("按ctrl+c退出\n");
	signal(SIGINT,fa);

	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd<0)
	{
		perror("socket");
		exit(-1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = bind(fd,(struct sockaddr *)&addr,sizeof(addr));
	if(res<0)
	{
		perror("bind");
		exit(-1);
	}
	printf("绑定成功,欢迎访问!\n");

	listen(fd,10);//监听客户端的连接
	while(1)
	{
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		int sockfd = accept(fd,(struct sockaddr *)&client,&len);
		if(sockfd<0)
		{
			perror("accept");
			exit(-1);
		}
		printf("%s连接上来\n",inet_ntoa(client.sin_addr));
		pid_t pid = fork();
		if(!pid)
		{
			char buf[100] = {};
			while(1)
			{
				res = read(sockfd,buf,sizeof(buf));
				if(res<0)
				{
					perror("read");
					exit(-1);
				}
				if(res==0)
					break;
				printf("%s\n",buf);
				if(strcmp(buf,"bye")==0)
					break;
				write(sockfd,buf,strlen(buf));
				memset(buf,0,strlen(buf));//内存数值设置函数
			}
			close(sockfd);
			exit(0);
		}
		close(sockfd);
	}
}


