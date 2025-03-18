#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define handle_error(cmd, result) \
    if (result < 0)               \
    {                             \
        perror(cmd);              \
        return -1;                \
    }


void *read_from_client_then_write(void *arg)
{
    //读取客户端发送过来的数据 回复收到
    int client_fd = *(int *)arg;
    char *read_buf = NULL;
    char *write_buf = NULL;
    ssize_t count = 0, send_count = 0;

    read_buf = malloc(sizeof(char) * 1024);
    write_buf = malloc(sizeof(char) * 1024);

    if(!read_buf){
        printf("初始化读缓冲失败\n");
        close(client_fd);
        perror("read_buf");
        return NULL;
    }
    if(!write_buf){
        printf("初始化写缓冲失败\n");
        close(client_fd);
        perror("write_buf");
        return NULL;
    }

    while (count = recv(client_fd,read_buf,1024,0))
    {
        if(count < 0){
            perror("recv");
        }
        //接收数据打印到控制台
        printf("从%d客户端收到数据%s\n", client_fd, read_buf);
        strcpy(write_buf, "收到\n");
        send_count = send(client_fd, write_buf, 1024, 0);
        if (send_count < 0)
        {
            perror("send");
        }
    }
    //当客户端输入ctrl+d时会退出循环
    close(client_fd);
    free(read_buf);
    free(write_buf);
}

//关闭回收所有的子进程 避免僵尸进程
void zombie_dealer(int sig) {
        pid_t pid;
        int status;
        // 一个SIGCHLD可能对应多个子进程的退出
        // 使用while循环回收所有退出的子进程，避免僵尸进程的出现
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
            if (WIFEXITED(status)) {
                printf("子进程: %d 以 %d 状态正常退出，已被回收\n", pid, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("子进程: %d 被 %d 信号杀死，已被回收\n", pid, WTERMSIG(status));
            } else {
                printf("子进程: %d 因其它原因退出，已被回收\n", pid);
            }
        }
    }

int main(int argc, char const *argv[])
{
    int sockfd, temp_result;
    struct sockaddr_in server_addr, client_addr;

    //注册信号处理函数 sigchild
    signal(SIGCHLD, zombie_dealer);

    //清空
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));    

    //填写服务器地址
    server_addr.sin_family = AF_INET;//协议
    //填写ip地址 0.0.0.0
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //填写端口号
    server_addr.sin_port = htons(6666);

    //网络编程流程
    //1.创建socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockfd);

    //2.绑定地址
    temp_result = bind(sockfd, &server_addr, sizeof(server_addr));
    handle_error("bind", temp_result);

    //3.进入监听状态
    temp_result = listen(sockfd, 128);
    handle_error("listen", temp_result);

    //4.获取客户端的连接
    //需要能够接收多个连接
    socklen_t cliaddr_len = sizeof(client_addr);
    while (1)
    {
        int clientfd = accept(sockfd, &client_addr, &cliaddr_len);
        pthread_t pid_read_write;
        handle_error("accept", clientfd);
        printf("与客户端%s %d建立连接%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), clientfd);
        //创建单独的子进程和连接的客户端交互
        pid_t pid = fork();
        if(pid < 0)
        {
            perror("fork");
        }else if(pid == 0)
        {
            //子进程
            //关闭不会使用的sockfd
            close(sockfd);
            printf("与客户端%s %d建立连接%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), clientfd);
            //从客户端读取数据 并回复
            read_from_client_then_write((void *)&clientfd);
            //关闭client_fd
            close(clientfd);
            exit(EXIT_SUCCESS);
        }else
        {
            //父进程
            //关闭掉不使用的clientfd
            close(clientfd);
        }
    }
    printf("释放资源\n");
    close(sockfd);

    return 0;
}
