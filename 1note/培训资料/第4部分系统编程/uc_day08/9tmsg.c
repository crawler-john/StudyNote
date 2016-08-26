#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct Msg
{
	long mtype;
	char buf[100];
};

int main()
{
	key_t key = ftok(".",100);
	int msgid = msgget(key,IPC_CREAT|0666);
	if(msgid<0)
	{
		perror("msgget");
		exit(-1);
	}
	
	struct Msg msg1,msg2;
	msg1.mtype = 1;
	strcpy(msg1.buf,"zhangfei");
	msg2.mtype = 2;
	strcpy(msg2.buf,"guanyu");
	int res1 = msgsnd(msgid,&msg1,sizeof(msg1.buf),0);
	int res2 = msgsnd(msgid,&msg2,sizeof(msg2.buf),0);
	if((res1!=-1)&&(res2!=-1))
	{
		printf("send success!\n");
	}

	return 0;
}
