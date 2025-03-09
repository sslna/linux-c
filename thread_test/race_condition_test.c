#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 20000

//初始化锁
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *add_thread(void *arg)
{
    //转化传入的参数
    int *p = (int *)arg;

    //在累加之前 获取锁 保证同一时间只有一个线程对其累加
    pthread_mutex_lock(&counter_mutex);
    (*p)++;
    //累加完之后 释放锁
    pthread_mutex_unlock(&counter_mutex);
    
    return (void *)0;
}

int main(int argc, char const *argv[])
{
    pthread_t pid[THREAD_COUNT];
    int num = 0;
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        //创建的线程功能是给传入的参数累加1
        pthread_create(pid + i, NULL, add_thread, &num);
    }

    //等待所有的线程执行完毕
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(pid[i], NULL);
    }

    //打印最终的累加结果
    printf("累加的结果是%d\n", num);

    return 0;
}

