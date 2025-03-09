#include <stdio.h>

int main(int argc, char const *argv[])
{
    //打开文件
    FILE *ioFile = fopen("io.txt", "r");
    if(ioFile==NULL)
    {
        printf("打开失败");
    }
    else{}

    //读取文件内容
    /*
    extern int fgetc (FILE *__stream);
    return：读取的一个字节 如果出错或者到文件的末尾则返回EOF
    FILE *__stream
    */
    char c = fgetc(ioFile);
    while (c!=EOF)
    {
        printf("%c", c);
        c = fgetc(ioFile);
    }
    printf("\n");
    //关闭文件
    fclose(ioFile);

    return 0;
}
