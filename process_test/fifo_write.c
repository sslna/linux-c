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
    if (mkfifo(pipe_path,0664)!=0)
    {
        perror("mkfifo");
        //忽略file exist的错误
        if (errno!=EEXIST)
        {
            exit(EXIT_FAILURE);
        }
        
    }

    //对有名管道的特殊文件 创建fd
    fd = open(pipe_path, O_WRONLY);
    if(fd==-1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    char write_buf[100];
    ssize_t read_num;
    //读取控制台数据写入到管道中
    while ((read_num=read(STDIN_FILENO,write_buf,100))>0)
    {
        write(fd, write_buf, read_num);
    }
    if(read_num<0)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("发送数据到管道完成 进程终止\n");
    close(fd);

    //释放管道
    //清除对应的特殊文件
    if(unlink(pipe_path)==-1)
    {
        perror("unlink");
    }

    return 0;
}
