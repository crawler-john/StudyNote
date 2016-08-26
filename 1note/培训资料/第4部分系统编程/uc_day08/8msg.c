#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	//通过ftok()获取key，这个key可以和共享内存相同
	key_t key = ftok(".",100);
	//通过key获取一个消息队列，同时获得他的ID
	int msgid = msgget(key,0);
	if(msgid<0)
	{
		perror("msgget");
		exit(-1);
	}
	//从消息队列接受无类型的消息
	char buf[1024];
	int res = msgrcv(msgid,buf,sizeof(buf),0,0);
	if(res!=-1)
		printf("读到了%d字节，内容是%s\n",res,buf);
	else
		perror("msgrcv");

	return 0;
}

