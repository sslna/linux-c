#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h> 

//定义结构体接收线程结果
typedef struct Result{
    char *p;
    int len;
} Result;

//如果一个进程的多个线程同时使用标准的输入输出 会造成冲突的问题
//导致只能有一个线程使用到标准的输入输出

//红玫瑰执行代码的函数
void *red_thread(void *argv)
{
    //初始化结构体
    Result *result = malloc(sizeof(Result));
    //解析传递的参数
    char code = *((char *)argv);
    //声明存放读取信息的字符串
    char *ans = malloc(101);
    while (1)
    {
        fgets(ans, 100, stdin);
        if(ans[0]==code)
        {
            //接到了回复的消息
            free(ans);
            printf("红玫瑰离开了\n");
            char *redans = strdup("红玫瑰独自去了纽约");
            result->p = redans;
            result->len = strlen(redans);
            //结束线程 返回故事结果
            pthread_exit((void *)result);
        }else{
            printf("红玫瑰还在等你");
        }
    }
}

//白玫瑰执行代码的函数
void *white_thread(void *argv)
{
    //初始化结构体
    Result *result = malloc(sizeof(Result));
    //解析传递的参数
    char code = *((char *)argv);
    //声明存放读取信息的字符串
    char *ans = malloc(101);
    while (1)
    {
        fgets(ans, 100, stdin);
        if(ans[0]==code)
        {
            //接到了回复的消息
            free(ans);
            printf("白玫瑰离开了\n");
            char *redans = strdup("白玫瑰独自去了巴黎");
            result->p = redans;
            result->len = strlen(redans);
            //结束线程 返回故事结果
            pthread_exit((void *)result);
        }else{
            printf("白玫瑰还在等你");
        }
    }
}


int main(int argc, char const *argv[])
{
    //回复红玫瑰与白玫瑰为依据
    //创建两个线程 红玫瑰与白玫瑰线程
    pthread_t pid_red;
    pthread_t pid_white;
    char red_code = 'r';
    char white_code = 'w';
    Result *red_result = NULL;
    Result *white_result = NULL;

    //创建红玫瑰线程
    pthread_create(&pid_red, NULL, red_thread, &red_code);
    //创建白玫瑰线程
    pthread_create(&pid_white, NULL, white_thread, &white_code);

    //获取红玫瑰线程的结果
    pthread_join(pid_red, (void **)&red_result);
    printf("红玫瑰故事的结局是：%s\n", red_result->p);
    //释放内存
    free(red_result->p);
    free(red_result);

    //获取白玫瑰线程的结果red
    pthread_join(pid_white, (void **)&white_result);
    printf("白玫瑰故事的结局是：%s\n", white_result->p);
    //释放内存
    free(white_result->p);
    free(white_result);    

    return 0;
}
