#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int shared_data = 0;

void *lock_writer(void *arg)
{
    //给多个线程写入添加写锁
    //同一时间只能由一个线程获取写锁 会造成两个线程顺序执行
    printf("我%s要获取写锁\n", (char *)arg);
    pthread_rwlock_wrlock(&rwlock);
    int tmp = shared_data + 1;
    shared_data = tmp;
    printf("当前是%s，shared_data是%d\n", (char *)arg, shared_data);
    //写入完成之后释放锁
    pthread_rwlock_unlock(&rwlock);
    printf("我%s释放写锁\n", (char *)arg);
}

void *lock_reader(void *arg)
{   
    //读写锁中的读是可以由多个线程统一读取的
    //获取读锁
    printf("我%s要获取读锁\n", (char *)arg);
    pthread_rwlock_rdlock(&rwlock);
    printf("当前是%s,shared_data是%d\n", (char *)arg, shared_data);
    sleep(1);
    pthread_rwlock_unlock(&rwlock);
    printf("我%s释放读锁\n", (char *)arg);

}

int main(int argc, char const *argv[])
{
    //显式初始化读写锁
    pthread_rwlock_init(&rwlock,NULL);

    pthread_t write1, write2,reader1,reader2,reader3,reader4,reader5,reader6;
    pthread_create(&write1, NULL, lock_writer, "writer1");

    pthread_create(&reader1, NULL, lock_reader, "reader1");
    pthread_create(&reader2, NULL, lock_reader, "reader2");
    pthread_create(&reader3, NULL, lock_reader, "reader3");
    //在线程读取数据的时候 中间添加一个获取写锁的写操作
    pthread_create(&write2, NULL, lock_writer, "writer2");
    pthread_create(&reader4, NULL, lock_reader, "reader4");
    pthread_create(&reader5, NULL, lock_reader, "reader5");
    pthread_create(&reader6, NULL, lock_reader, "reader6");

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
