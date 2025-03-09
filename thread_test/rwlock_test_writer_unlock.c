#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int shared_data = 0;

void *lock_writer(void *arg)
{
    int tmp = shared_data + 1;
    sleep(1);
    shared_data = tmp;
    printf("当前是%s，shared_data是%d\n", (char *)arg, shared_data);
}

void *read_writer(void *arg)
{   
    //读写锁中的读是可以由多个线程统一读取的
    //获取读锁
    pthread_rwlock_rdlock(&rwlock);
    printf("当前是%s,shared_data是%d\n", (char *)arg, shared_data);
    pthread_rwlock_unlock(&rwlock);
}

int main(int argc, char const *argv[])
{
    //显式初始化读写锁
    pthread_rwlock_init(&rwlock,NULL);

    pthread_t write1, write2,reader1,reader2,reader3,reader4,reader5,reader6;
    pthread_create(&write1, NULL, lock_writer, "writer1");
    pthread_create(&write2, NULL, lock_writer, "writer2");
    //休眠等待
    sleep(3);

    pthread_create(&reader1, NULL, read_writer, "reader1");
    pthread_create(&reader2, NULL, read_writer, "reader2");
    pthread_create(&reader3, NULL, read_writer, "reader3");
    pthread_create(&reader4, NULL, read_writer, "reader4");
    pthread_create(&reader5, NULL, read_writer, "reader5");
    pthread_create(&reader6, NULL, read_writer, "reader6");

    //主线程等待创建的子线程运行完成
    pthread_join(write1,NULL);
    pthread_join(write2,NULL);
    pthread_join(reader1,NULL);
    pthread_join(reader2,NULL);
    pthread_join(reader3,NULL);
    pthread_join(reader4,NULL);
    pthread_join(reader5,NULL);
    pthread_join(reader6,NULL);

    //销毁读写锁
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
