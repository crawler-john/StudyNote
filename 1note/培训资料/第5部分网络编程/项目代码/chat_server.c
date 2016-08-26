//TCP聊天室服务器
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
struct client{
	char name[20];//客户端连接上来时 输入的姓名
	int fds;//客户端的socket
};
struct client c[100]={0};//最多记录100个sockfd,最多允许100个用户进入
int sockfd;//服务器的sockfd
int size = 0;//记录客户端的个数,数组的索引
char filename[4096] = {0};
char* IP = "127.0.0.1";//获取本机IP
short PORT = 10222;
typedef struct sockaddr SA;//用作通信地址类型转换的时候使用

//初始化服务器的网络,创建socket..
void init(){
	printf("聊天室服务器开始启动..\n");
	//创建socket
	sockfd = socket(PF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		perror("创建socket失败");
		printf("服务器启动失败\n");
		exit(-1);
	}
	//准备通信地址
	struct sockaddr_in addr;//网络通信的地址信息
	addr.sin_family = PF_INET;//协议簇
	addr.sin_port = htons(PORT);//端口
	addr.sin_addr.s_addr = inet_addr(IP);//IP地址结构体
	//绑定socket和通信地址
	if(bind(sockfd,(SA*)&addr,sizeof(addr))==-1){
		perror("绑定失败");
		printf("服务器启动失败\n");
		exit(-1);
	}
	printf("成功绑定\n");
	//设置监听
	if(listen(sockfd,100)==-1){
		perror("设置监听失败");
		printf("服务器启动失败\n");
		exit(-1);
	}
	printf("设置监听成功\n");
	printf("初始化服务器成功\n");
	//等待客户端连接和通信部分写到另一个函数中
}
//用来分发消息的函数
void sendMsgToAll(char * msg){
	int i=0;
	for(;i<size;i++){
		if(c[i].fds!=0){
			printf("sendto****%d\n",c[i].fds);
			send(c[i].fds,msg,strlen(msg),0);//
			}
		}
	}
//线程函数，用来接受客户端的消息，并把消息分发给所有的客户
void * service_thread(void* p){
		int m_id = 0;
		char name[20]={};
		if(recv(c[size].fds,name,sizeof(name),0)>0){//接受到名字
			strcpy(c[size].name,name);
		}
		m_id = size;
		size++;
	//进入线程之后，先群发一条提示，提示某某客户端连接上来
	char tishi[100]={};
	sprintf(tishi,"热烈欢迎 %s 登录本聊天室..",c[size-1].name);
	sendMsgToAll(tishi);
	int fd = *(int*)p;
	printf("pthread=%d\n",fd);//线程所对应的客户端的描述符
	//通信,接受消息，分发消息
	while(1)
	{
		char buf[100]={};
		if(recv(fd,buf,sizeof(buf),0)<=0)
		{//接受信息
			printf("fd=%dquit\n",fd);//recv函数返回小于0，则
			//表示有客户端断开，打印quit
			//之后将退出的客户端的socket描述符重新置成0
			int i;
			for(i=0;i<size;i++)
			{
				if(c[i].fds==fd)
				{
						c[i].fds=0;
						break;
				}
			}
			printf("quit->fd=%dquit\n",fd);//打印fd->quit退出
			char msg[100]={};
			sprintf(msg,"欢送 %s 离开聊天室,再见..",c[i].name);
			//将退出消息发给所有聊天的人
			//将这些内容写到一个函数中
			sendMsgToAll(msg);
			return ;//某客户端退出之后，结束线程
		}//正确读到数据之后
		if(strncmp(buf,"TF",2) == 0)
		{//接收文件
			if(recv(fd,filename,sizeof(filename),0)<0)
			{//接收文件名
				perror("recv filename");
				printf("服务器接收文件%s失败",filename);
				continue;
			}
			//开始接收文件内容
			FILE* fp = fopen(filename,"wb");
			if(fp == NULL)
			{
				perror("open filename ");
				printf("服务器接收文件%s失败",filename);
				continue;					
			}
			char buff[4096] = {0};
			int res = 0;
			int flag = 1;
			while((res=recv(fd,buff,4096,0)) == 4096)
			{
				if(res < 0)
				{
					perror("recv ");
					printf("服务器接收文件%s失败",filename);
					flag = 0;
					break;
				}
				int writelen = fwrite(buff,sizeof(char),res,fp);///////////////
					
				if(writelen < res)
				{
					perror("fwrite ");
					printf("服务器接收文件%s失败",filename);
					flag = 0;
					break;
				}
				bzero(buff,4096);//清零数组
			}
			if( res>0 )
			{
				int writelen = fwrite(buff,sizeof(char),res,fp);
				if(writelen < res)
				{
					perror("fwrite ");
					printf("服务器接收文件%s失败",filename);
					flag = 0;
					break;
				}
			}
			if(flag!=1)
			{
				fclose(fp);
				continue;
			}
			printf("成功接收到客户端的文件\n");
			fclose(fp);
		}
		else
		{
			char msg[100] = {0};
			sprintf(msg,"%s 说: %s",c[m_id].name,buf);
			sendMsgToAll(msg);
		}
		bzero(buf,100);
	}
}
//等待客户端连接，启动服务器的服务
void service(){
	printf("服务器开始服务\n");
	while(1){
		struct sockaddr_in fromaddr;//存储客户端的通信地址
		socklen_t len = sizeof(fromaddr);
		int fd = accept(sockfd,(SA*)&fromaddr,&len);
		if(fd == -1){
			printf("客户端连接出错..\n");
			continue;//继续下一次循环，等待客户端连接
		}
		//如果客户端顺利连接上来，那记录它的socket描述符，
		//并开启一个线程，为此客户端服务
		//记录客户端的socket
		c[size].fds = fd;
		printf("fd=%d\n",fd);
		//开启线程
		pthread_t pid;
		pthread_create(&pid,0,service_thread,&c[size].fds);
	}
}
void sig_close(){
	//关闭服务器的socket
	close(sockfd);
	printf("服务器已经关闭..\n");
	exit(0);
}
int main(){
	//发信号，ctrl+c 然后关闭socket
  signal(SIGINT,sig_close);//自定义信号处理函数，做好善后工作，关闭socket
	//初始化网络
	init();
	//启动服务
	service();
	return 0;
}

