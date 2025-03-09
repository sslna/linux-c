#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //跳转之前
    char *name = "banzhang";
    printf("我是%s 编号%d，我现在还在一楼\n", name, getpid());

    //执行跳转
    /**
     * extern int execve (const char *__path, char *const __argv[],
		   char *const __envp[]) 

        char *__path: 需要执行程序的完整路径名
        char *const __argv[]: 指向字符串数组的指针 需要传入多个参数
        (1) 需要执行的程序命令(同*__path)
        (2) 执行程序需要传入的参数
        (3) 最后一个参数必须是NULL

        char *const __envp[]: 指向字符串数组的指针 需要传入多个环境变量参数
        (1) 环境变量参数 固定格式 key=value
        (2) 最后一个参数必须是NULL

        return: 成功就回不来了 下面的代码都没有意义
            失败返回-1
     * 
     */

    //下面把name传参传过去了
    char *args[] = {"/home/ssln/workspace/c/process_test/erlou", name, NULL};

    char *envs[] = {NULL};
    int re = execve(args[0], args, envs);
    return 0;
}
