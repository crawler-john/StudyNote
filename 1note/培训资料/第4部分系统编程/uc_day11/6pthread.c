#include <stdio.h>
#include <pthread.h>

int sum;

void *task(void *p)
{
    int i;
    for(i=1;i<11;i++)
        sum += i;
    pthread_exit((void *)sum);
}

void *task2(void *p)
{
    printf("hello\n");
    sleep(2);
    printf("bye\n");

    return p;
}

int main()
{
    pthread_t id;
    pthread_create(&id,0,task2,0);
    sleep(1);
    //pthread_join(id,0);
    pthread_cancel(id);
    printf("sum = %d\n",sum);

    return 0;
}
