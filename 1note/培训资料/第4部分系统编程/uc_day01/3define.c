#include <stdio.h>
#include <print.h>

void print(void)
{
	printf("__BASE_FILE__	:%s\n",__BASE_FILE__);
	printf("__FILE__	:%s\n",__FILE__);
	printf("__LINE__	:%d\n",__LINE__);
	printf("__FUNCTION__	:%s\n",__FUNCTION__);
	printf("__func__	:%s\n",__func__);
	printf("__DATE__	:%s\n",__DATE__);
	printf("__TIME__	:%s\n",__TIME__);
}

