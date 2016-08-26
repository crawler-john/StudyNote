//聊天室客户端
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

int sockfd;//客户端socket
char *IP="127.0.0.1";//本地IP
short PORT=10222;//服务器服务端口
typedef struct sockaddr SA;
char name[30];//用于存放聊天人的昵称

//客户端也分为几步:
//启动客户端，连接服务器
void init(){
	printf("聊天室客户端开始启动\n");
	sockfd=socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family = PF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(IP);
	if(connect(sockfd,(SA*)&addr,sizeof(addr))==-1){
		perror("无法连接到服务器");
		printf("客户端启动失败\n");
		exit(-1);
	}
	printf("客户端启动成功\n");
}
//开始通信
void start(){
	//发送消息之前
	//启动一个线程，用来接受服务器发过来的消息
	pthread_t pid;
	void* recv_thread(void*);//线程函数的声明
	pthread_create(&pid,0,recv_thread,0);
	char buf[100] = {0};
	while(1){//内部不断的发送数据
		printf("传输文件请输入TF:\n");
		bzero(buf,100);
		scanf("%s",buf);//读取客户端的输入信息
		if(strncmp(buf,"TF",2) == 0){
			send(sockfd,"TF",2,0);//文件传输标志
			//说明要传输文件
			printf("请输入要传送的文件名:");
			char filename[100] = {};
			scanf("%s",filename);
			FILE* fp = fopen(filename,"rb");
			if(fp == NULL){
				perror("fopen");
				printf("文件传输失败\n");
				continue;
			}	
			else{
				//文件能打开 就把文件名字传给服务器。
				send(sockfd,filename,strlen(filename),0);
				char buff[4096] = {0};
				int res = 0;
				int flag = 1;
				while((res = fread(buff,sizeof(char),4096,fp))
						>0){
					if(send(sockfd,buff,res,0)<0){
						perror("Send file");
						flag = 0;
						break;
					}
					bzero(buff,4096);//将缓冲区清零
				}
				if(feof(fp))fclose(fp);
				else {perror("fread");continue;}
				if(flag!=1){
					printf("传输文件失败\n");	
					continue;//直接到下一次循环，等待用户输入
				}
			}
			printf("Transfer file finished !\n");
		}
		else{
			send(sockfd,buf,strlen(buf),0);//发送消息给服务器
		}
	}
}
void * recv_thread(void* p){
	while(1){
		char buf[100]={};//存储读到的消息
		if(recv(sockfd,buf,sizeof(buf),0)<=0){//接收出错
			return ;//结束线程
		}
		printf("%s\n",buf);
	}
}
void sig_close(){
	//关闭客户端的socket
	close(sockfd);
	exit(0);
}
int main(){
	//f发信号，关闭socket
	signal(SIGINT,sig_close);//自定义信号处理函数，做好善后工作	
	printf("请输入您的名字:");
	scanf("%s",name);
	init();//启动客户端，连接服务器
	send(sockfd,name,strlen(name),0);//把名字给服务器
	start();//通信
}

注意：
   一般错误原因