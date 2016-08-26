#include <stdio.h>

#pragma GCC dependency "1error.c"
#pragma GCC poison int

int main()
{
	int num = 1;
	printf("%d\n",__LINE__);
	#line 100
	printf("%d\n",__LINE__);

	return 0;
}
