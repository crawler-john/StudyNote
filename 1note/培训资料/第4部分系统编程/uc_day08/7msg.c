#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	//通过ftok()获取key，这个key可以和共享内存相同
	key_t key = ftok(".",100);
	//通过key创建一个消息队列，同时获得他的ID
	int msgid = msgget(key,IPC_CREAT|0666);
	if(msgid<0)
	{
		perror("msgget");
		exit(-1);
	}
	//往消息队列发送无类型的消息
	int res = msgsnd(msgid,"hello",5,0);
	if(!res)
		printf("发送成功！\n");
	else
		perror("msgsnd");

	return 0;
}

