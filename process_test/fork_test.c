#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //调用fork之前 代码都在父进程中运行
    printf("老师教学员%d学习\n", getpid());

    //使用fork创建子进程

    /**
     * __pid_t fork (void)
     * return:int 进程号
     *      （1）-1 出错
     *      （2）：父进程中显示子进程的pid
     *      （3）：子进程中显示为0
     */

    pid_t pid = fork();
    //从fork之后，所有的代码都是在父子进程中各执行一次的

    printf("%d\n", pid);
    if(pid<0)
    {
        printf("失败");
        return 1;
    }
    else if(pid == 0)
    {
        //单独子进程的代码
        printf("新学员%d加入成功，他是老学员%d推荐的\n", getpid(), getppid());

    }
    else
    {
        //单独父进程的代码
        printf("老学员%d继续深造，他推荐了%d\n", getpid(), pid);
    }

    return 0;
}
