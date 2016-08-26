#include <stdio.h>
#include <pthread.h>

void *task(void *p)
{
    int i;
    for(i=0;i<50;i++)
    {
        printf("%d\n",i);
        usleep(100000);//0.1s
    }
}

int main()
{
    pthread_t id;
    pthread_create(&id,0,task,0);
    //把线程设置成分离状态
    pthread_detach(id);
    pthread_join(id,0);//detach的线程join没有效果
    int i;
    for(i=0;i<50;i++)
    {
        printf("main:%d\n",i);
        usleep(100000);//0.1s
    }

    return 0;
}
