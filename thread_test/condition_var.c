#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

//静态初始化互斥锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//初始化条件变量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//在buf中写数据
void *producer(void *arg)
{
    int item = 1;
    while (1)
    {
        //使用共同的变量 使用互斥锁 首先获取锁
        pthread_mutex_lock(&mutex);

        //如果缓冲区写满 使用条件变量暂停当前线程
        if (count == BUFFER_SIZE)
        {
            //暂停线程
            pthread_cond_wait(&cond, &mutex);
        }
        //缓冲区没有满
        buffer[count++] = item++;
        printf("生产者发送了数字%d\n", buffer[count - 1]);
        //唤醒消费者
        pthread_cond_signal(&cond);
        //最后释放锁
        pthread_mutex_unlock(&mutex);
    }
}

//从buf中读数据
void *consumer(void * arg)
{
    while (1)
    {
        //使用共同的变量 使用互斥锁 首先获取锁
        pthread_mutex_lock(&mutex);
        if (count == 0)
        {
            //缓存中没有消息可读
            //暂停线程
            pthread_cond_wait(&cond, &mutex);
        }
        printf("消费者收到数字%d\n", buffer[--count]);

        //通知生产者可以继续写
        pthread_cond_signal(&cond);

        //最后释放锁
        pthread_mutex_unlock(&mutex);        
    }
    

}


int main(int argc, char const *argv[])
{
    //创建两个线程 一个向buf中写 一个从buf中读
    pthread_t producer_thread, consumer_thread;
    //创建生产者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    //创建消费者线程
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    //主线程需要挂起等待两个线程完成
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);    

    return 0;
}
