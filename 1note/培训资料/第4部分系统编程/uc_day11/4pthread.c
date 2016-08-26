#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *task(void *p)
{
    static int sum = 0;
    int i;
    for(i=1;i<11;i++)
        sum += i;

    //return (void *)sum;
    return (void *)&sum;
}

int main()
{
    pthread_t id;
    pthread_create(&id,0,task,0);
    //int num;
    int *p1;//野指针
    pthread_join(id,(void **)&p1);

    printf("sum = %d\n",*p1);

    return 0;
}
