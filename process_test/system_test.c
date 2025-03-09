#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    //使用标准库函数创建子进程
    /**
     * int system (const char *__command)
     * const char *__command：使用Linux命令直接创建一个子进程
     * return：成功返回0 失败返回错误编号
     */
    int sysR = system("ping -c 100 www.baidu.com");
    if (sysR!=0)
    {
        perror("system");
        exit(EXIT_FAILURE);
    }

    return 0;
}
