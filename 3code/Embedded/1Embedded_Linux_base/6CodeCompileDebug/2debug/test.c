#include <stdio.h>

int sum(int a,int b)
{
    return (a+b);
}

int main(void)
{
    int a = 10;
    int b = 20;
    int c = sum(a,b);
    printf("sum = %d\n",c);
}
