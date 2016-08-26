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
	int msgid = msgget(key,0);
	if(msgid<0)
	{
		perror("msgget");
		exit(-1);
	}
	
	struct Msg msg;
	int res = msgrcv(msgid,&msg,sizeof(msg.buf),/*1*/2,0);
	if(res==-1)
	{
		perror("msgrcv");
		exit(-1);
	}
	printf("%d,%s\n",res,msg.buf);

	msgctl(msgid,IPC_RMID,0);
	return 0;
}

