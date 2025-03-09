#include <stdio.h>

int main(int argc, char const *argv[])
{
    /*
    extern FILE *fopen (const char *__restrict __filename,
		    const char *__restrict __modes)
    const char *__restrict __filename :字符串表示要打开的文件名称
    const char *__restrict __modes) : 访问模式
        (1) r:只读模式 如果没有文件会报错
        (2) w:只写模式 如果文件存在则清空文件，不存在则创建新文件
        (3) a:只追加写模式 如果文件存在 末尾追加写 不存在则创建新文件
        (4) r+:读写模式 文件必须存在,写入是从头一个一个覆盖
        (5) a+:读追加写模式 如果文件存在 末尾追加写 不存在则创建新文件

    返回值：FILE * 结构体指针 表示一个文件
            报错返回NULL
    */
    char *filename="io.txt";
    FILE *ioFile = fopen(filename,"a");
    if (ioFile == NULL)
    {
        printf("failed\n");
    }
    else
    {
        printf("success!\n");
    }
    
    return 0;
}
