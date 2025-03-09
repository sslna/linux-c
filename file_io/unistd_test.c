#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    /**
     * int open (const char *__path, int __oflag, ...)
     * const char *__path：打开文件的路径
     * int __oflag：打开文件的模式
     *              (1) O_RDONLY: 以只读方式打开文件 
                    (2) O_WRONLY: 以只写方式打开文件 
                   （3) O_RDWR: 以读写方式打开文件 
                    (4) O_CREAT: 如果文件不存在,则创建一个新文件 
                    (5) O_APPEND: 将所有写入操作追加到文件的末尾 
                    (6) O_TRUNC: 如果文件存在并且以写入模式打开,则截断文件长度为0 
     */
    int fd = open("io1.txt", O_RDONLY | O_CREAT, 0664);
    if (fd==-1)
    {
        printf("failed\n");
    }

    return 0;
}
