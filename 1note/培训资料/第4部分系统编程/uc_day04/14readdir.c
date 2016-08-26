#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void printall(char *path)
{
	DIR *dir = opendir(path);
	if(dir==NULL)
		return;
	struct dirent *ent;
	while(ent=readdir(dir))
	{
		if(strcmp(".",ent->d_name)==0||strcmp("..",ent->d_name)==0)
			continue;
		if(ent->d_type==4)//目录
		{
			printf("[%s]\n",ent->d_name);
			char buf[100] = {};
			sprintf(buf,"%s/%s",path,ent->d_name);
			printall(buf);
		}
		else//文件
		{
			printf("%s\n",ent->d_name);
		}
	}
}


int main()
{
	printall("../");

	return 0;
}

