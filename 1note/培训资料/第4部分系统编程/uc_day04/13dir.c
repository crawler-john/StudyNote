#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main()
{
	DIR *dir = opendir("../");
	struct dirent *dirent = NULL;
	while(dirent = readdir(dir))
	{
		//d_type==4就是子目录
		printf("%d,%s\n",dirent->d_type,dirent->d_name);
	}

	closedir(dir);

	return 0;
}
