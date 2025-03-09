#include <stdio.h>

int main(int argc, char const *argv[])
{
    //打开文件
    FILE *ioFile = fopen("user.txt", "r");
    if(ioFile==NULL)
    {
        printf("打开失败");
    }
    else{}

    //读取文件内容
    /*
    extern int fscanf (FILE *__restrict __stream,
		   const char *__restrict __format, ...)
    FILE *__restrict __stream：打开的文件
    const char *__restrict __format：带有格式化的字符串
    ...：可变参数
    return:成功匹配到的参数的个数 如果匹配失败返回0
    */
    char name[50];
    int age;
    char name2[50];
    int res;
    while ((res = fscanf(ioFile, "%s %d %s", name, &age, name2))!=EOF)
    {
        printf("匹配到的参数有%d个\n", res);
        printf("%s %d %s\n", name, age, name2);    
    }

    //关闭文件
    fclose(ioFile);

    return 0;
}
