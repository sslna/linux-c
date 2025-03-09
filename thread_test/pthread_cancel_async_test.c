#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *task(void *arg)
{
    printf("thread started\n");
    //默认取消类型是延迟
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);//设置为异步取消
    printf("working...\n");
    int i = 0;
    while (1)
    {
        printf("%d\n", i++);
    }

    printf("after cancelled\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    //创建线程
    pthread_t tid;
    pthread_create(&tid, NULL, task, NULL);

    if(pthread_cancel(tid)!=0)
    {
        perror("pthread_cancel\n");
    }
    void *res;
    //pthread_cancel只是发出一个停止的命令
    //join会挂起 一直等待子线程运行结束
    pthread_join(tid, &res);

    if(res==PTHREAD_CANCELED)
    {
        printf("线程被取消\n");
    }else{
        printf("线程还没有被取消 exit code %ld", (long)res);
    }

    return 0;
}
