#include "show.h"
#include "cal.h"

int main()
{
	int a=5,b=3;
	
	show(a,'+',b,add(a,b));
	show(a,'-',b,sub(a,b));
	
	return 0;
}
