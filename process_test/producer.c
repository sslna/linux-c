#include <time.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    //创建消息队列
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;//消息的最大数量
    attr.mq_msgsize = 100;//单条消息的最大长度
    attr.mq_curmsgs = 0;


    char *mq_name = "/p_c_mq";
    mqd_t mqdes = mq_open(mq_name, O_RDWR | O_CREAT, 0664, &attr);
    if (mqdes==(mqd_t)-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    //不断接收控制台中的数据 发送到消息队列
    char write_buf[100];
    struct timespec time_info;
    while (1)
    {
        //清空缓冲区
        memset(write_buf, 0, 100);
        ssize_t read_count = read(STDIN_FILENO, write_buf, 100);
        clock_gettime(0, &time_info);//获取当前时间
        time_info.tv_sec += 5;
        if (read_count == -1)
        {
            perror("read");
            continue;
        }else if(read_count == 0)
        {
            //如果从控制台接收到停止发送的消息
            //ctrl+d关闭控制台输入
            printf("EOF,exit...\n");
            char eof = EOF;
            if(mq_timedsend(mqdes,&eof,1,0,&time_info)==-1)
            {
                perror("mq_timedsend");
            }
            break;
        }

        //正常接收到控制台的可读信息
        if(mq_timedsend(mqdes,write_buf,strlen(write_buf),0,&time_info)==-1)
        {
            perror("mq_timedsend");
        }
        printf("从命令行接收到数据 已经发送给消息队列\n");
    }

    //关闭消息队列描述符
    close(mqdes);

    

    return 0;
}
