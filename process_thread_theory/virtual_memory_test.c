#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int val = 123;
    __pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        // 子进程
        val = 321;
        printf("子进程中val 的内容是: %d\nval 所在的地址是: %p\n", val, &val);
    }
    else
    {
        // 父进程
        sleep(1);
        printf("父进程中val 的内容是: %d\nval 所在的地址是: %p\n", val, &val);
    }
    return 0;
}
