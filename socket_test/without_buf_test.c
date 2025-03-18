#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    FILE *file = fopen("/home/ssln/workspace/c/linux&c/socket_test/testfile.txt", "w");
    if(file==NULL)
    {
        perror("fopen");
        return 1;
    }

    //修改刷写模式
    setvbuf(file, NULL, _IONBF, 0);
    // 文件写入是全缓冲 等待缓冲区满或者手动刷写
    fprintf(file, "hello");
    //可以使用手动刷写
    //fflush(file);
    
    char *args[] = {"/usr/bin/ping", "-c", "1", "www.baidu.com", NULL};
    char *envs[] = {NULL};
    execve(args[0], args, envs);

    //如果跳转失败
    perror("execve");

    return 0;
}
