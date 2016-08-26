#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main()
{
	struct stat st;
	int res = stat("a.txt",&st);
	printf("inode = %d\n",st.st_ino);//节点
	printf("nlink = %d\n",st.st_nlink);
	printf("size = %d\n",st.st_size);//大小
	printf("time = %s\n",ctime(&st.st_mtime));
	printf("mode = %o\n",st.st_mode);
	printf("access = %o\n",st.st_mode&0777);
	if(S_ISREG(st.st_mode))
		printf("普通文件!\n");
	if(S_ISDIR(st.st_mode))
		printf("目录！\n");

	return 0;
}
