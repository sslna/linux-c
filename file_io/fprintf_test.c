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
    int fprintf (FILE *__restrict __stream, const char *__restrict __fmt, ...)
    FILE *__restrict __stream：打开的文件
    const char *__restrict __fmt：填入格式化的长字符串
    return：成功返回写入的字符的个数 不包含换行符 失败返回EOF
    */
    char *name = "name";
    int res = fprintf(ioFile, "test: %s\n", name);
    if(res==EOF)
    {
        printf("error");
    }
    else
    {
        printf("success %d",res);
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
