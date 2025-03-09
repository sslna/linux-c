#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    //使用共享内存
    char *shm_name = "unnamed_sem_shm";
    int fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    //调整共享内存大小
    ftruncate(fd, sizeof(sem_t));
    //完成映射
    sem_t *sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    //初始化信号量
    sem_init(sem, 1, 0);
    //创建父子进程
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
    }else if (pid == 0)
    {
        //子进程
        sleep(1);
        printf("这是子进程\n");
        sem_post(sem);
    }else
    {
        //父进程
        //子进程睡眠1s 保证父进程先执行
        sem_wait(sem);
        printf("这是父进程\n");
        waitpid(pid, NULL, 0);
    }

    //回收资源
    if (pid > 0)
    {
        if (sem_destroy(sem) == -1)
        {
            perror("sem_destroy");
        }
    }

    //父子进程都需要关闭文件描述符
    if (munmap(sem,sizeof(sem_t)) == -1)
    {
        perror("munmap");
    }
    if (close(fd) == -1)
    {
        perror("close");
    }

    if(pid > 0)
    {
        if(shm_unlink(shm_name) == -1)
        {
            perror("unlink");
        }
    }

    return 0;
}
