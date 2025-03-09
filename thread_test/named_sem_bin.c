#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    char *shm_value_name = "named_sem_shm_value";
    //创建有名信号量
    char *sem_name = "/named_sem_shm";

    // 创建内存共享对象
    int value_fd = shm_open(shm_value_name, O_CREAT | O_RDWR, 0666);

    //初始化有名信号量
    sem_t *sem = sem_open(sem_name, O_CREAT, 0666, 1);//设置初值为1

    // 调整内存共享对象的大小
    ftruncate(value_fd, sizeof(int));
    // 将内存共享对象映射到共享内存区域
    int *value = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, value_fd, 0);


    // 初始化共享变量的值
    *value = 0;
    //初始化信号量
    int pid = fork();

    if (pid > 0) {
        //父进程
        //信号量等待
        sem_wait(sem);
        int tmp = *value + 1;
        sleep(1);
        *value = tmp;
        //信号量唤醒
        sem_post(sem);

        // 等待子进程执行完毕
        waitpid(pid, NULL, 0);
        printf("this is father, child finished\n");
        printf("the final value is %d\n", *value);
    } else if (pid == 0) {
        //子进程
        sem_wait(sem);
        int tmp = *value + 1;
        sleep(1);
        *value = tmp;
        sem_post(sem);
    }
    else
    {
        perror("fork");
    }

    //父进程执行到这里 子进程已经执行完毕 摧毁信号量
    if (pid > 0)
    {

        }
    

    // 无论父子进程都应该解除共享内存的映射，并关闭共享对象的文件描述符
    if (munmap(value, sizeof(int)) == -1)
    {
        perror("munmap value");
    }

    //父子进程都需要close有名信号量
    if(sem_close(sem) == -1)
    {
        perror("sem_close");
    }

    if (close(value_fd) == -1)
    {
        perror("close value");
    }

    // 如果调用时别的进程仍在使用共享对象，则等待所有进程释放资源后，才会销毁相关资源。
    // shm_unlink只能调用一次,这里在父进程中调用shm_unlink
    if (pid > 0)
    {
        if (shm_unlink(shm_value_name) == -1)
        {
            perror("father shm_unlink shm_value_name");
        }
        if(sem_unlink(sem_name) == -1)
        {
            perror("sem_unlink");
        }
    }

    return 0;
}