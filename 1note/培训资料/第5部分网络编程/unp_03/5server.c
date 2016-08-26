#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

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
	struct sockaddr_in addr;//socket网络通信的地址
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
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
	char buf[100] = {};
	struct sockaddr_in from;
	socklen_t length = sizeof(from);
	while(1)
	{
		int len = recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr *)&from,&length);
		//printf("读到了%d个字节,内容%s\n",len,buf);
		time_t curtime = time(0);
		struct tm *cur = localtime(&curtime);
		sprintf(buf,"%d-%02d-%02d %02d:%02d:%02d",cur->tm_year+1900,
		cur->tm_mon+1,cur->tm_mday,cur->tm_hour,cur->tm_min,cur->tm_sec);
		sendto(fd,buf,strlen(buf),0,(struct sockaddr *)&from,length);
	}
	//5.关闭socket描述符
	close(fd);

	return 0;
}

