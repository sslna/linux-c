#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *task(void *arg)
{
    printf("thread started\n");
    sleep(2);
    printf("thread finished\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    //创建线程
    pthread_t tid;
    pthread_create(&tid, NULL, task, NULL);

    //使用detach标记会等待线程完成之后回收相关资源
    pthread_detach(tid);

    //主线程运行完成比创建的子线程慢
    printf("main thread continue\n");
    sleep(3);//因为主线程不会在pthread_detach等待 如果父进程先结束 会强制杀死子进程

    printf("main thread ending\n");

    return 0;
}
