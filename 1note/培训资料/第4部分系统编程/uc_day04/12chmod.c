#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	chmod("a.txt",0666);
	truncate("a.txt",100);
	int fd1 = open("aaa",O_RDWR|O_CREAT,0666);
	mode_t old = umask(0002);//修改屏蔽字
	int fd2 = open("bbb",O_RDWR|O_CREAT,0666);
	umask(old);//恢复默认
	int fd3 = open("ccc",O_RDWR|O_CREAT,0666);
	close(fd1);
	close(fd2);
	close(fd3);

	return 0;
}
