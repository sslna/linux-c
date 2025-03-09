#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int fd;
    char *pipe_path = "/tmp/myfifo1";
    //write创建管道 read无需再创建管道
    // if (mkfifo(pipe_path,0664)!=0)
    // {
    //     perror("mkfifo");
    //     exit(EXIT_FAILURE);
    // }

    //对有名管道的特殊文件 创建fd
    fd = open(pipe_path, O_RDONLY);
    if(fd==-1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    char read_buf[100];
    ssize_t read_num;
    //读取管道信息写入到控制台中
    while ((read_num=read(fd,read_buf,100))>0)
    {
        write(STDOUT_FILENO, read_buf, read_num);
    }
    if(read_num<0)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("接收管道数据完成 进程终止\n");
    close(fd);

    return 0;
}
