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

    /*
    读写权限记录在fopen函数中的参数
    extern int fputc (int __c, FILE *__stream);
    int __c：ASCII码对应的字符
    FILE *__stream：打开的一个文件
    返回值：成功返回char，失败返回EOF
    */

    int put_result = fputc(97, ioFile);
    if (put_result==EOF)
    {
        printf("写入失败\n");
    }
    else
    {
        printf("写入%c成功\n", put_result);
    }

    /*
    extern int fclose (FILE *__stream);
    FILE *__stream:需要关闭的文件
    返回值：成功返回0，失败返回EOF（负数） 通常关闭文件失败会直接报错
    */

    int result = fclose(ioFile);
    if (result == EOF)
    {
        printf("failed!\n");
    }
    else
    {
        printf("success!\n");
    }

    return 0;
}
