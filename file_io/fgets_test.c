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
    char * fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
    char *__restrict __s：接收读取到的字符串
    int __n：接收h数据的长度
    FILE *__restrict __stream：打开要读取的文件
    return：成功返回字符串，失败返回NULL
    */
    char buffer[100];
    while (fgets(buffer,sizeof(buffer),ioFile))
    {
        printf("%s", buffer);
    }


    //关闭文件
    fclose(ioFile);

    return 0;
}
