#include <stdio.h>

#define VERSION 3

#if (VERSION<3)
//	#error "版本太低!"
	#warning "版本太低!"
#elif (VERSION>3)
//	#error "版本太高!"
	#warning "版本太高!"
#endif

int main()
{
	printf("版本:%d\n.",VERSION);
	return 0;
}

