#include <glib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void task_func(gpointer data,gpointer user_data)
{
    int task_num = *(int *)data;
    free(data);
    printf("开始执行%d任务\n", task_num);
    sleep(task_num);
    printf("%d任务执行完成\n", task_num);
}

int main(int argc, char const *argv[])
{
    //创建线程池
    GThreadPool *pool = g_thread_pool_new(task_func, NULL, 5, TRUE, NULL);
    //向线程池中添加任务
    for (size_t i = 0; i < 10; i++)
    {
        int *tmp = malloc(sizeof(int));
        *tmp = i + 1;
        g_thread_pool_push(pool, tmp, NULL);
    }
    g_thread_pool_free(pool, FALSE, TRUE);
    printf("所有的任务都完成了\n");

    return 0;
}
