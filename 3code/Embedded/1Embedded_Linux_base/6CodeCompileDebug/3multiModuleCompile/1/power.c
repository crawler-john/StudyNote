#include <math.h>
#include <stdio.h>

int main(void)
{
	float x,y;
	printf("the program take x and from stdin and display x^y.\n ");
	printf("enter number x:");
	scanf("%f",&x);
	printf("enter number y:");
	scanf("%f",&y);
	printf("x^y is %6.3f\n",pow((double)x,(double)y));

}
