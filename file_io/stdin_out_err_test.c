#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char *ch = malloc(100);
    //从标准输入中读取数据
    fgets(ch, 100, stdin);
    printf("%s", ch);
    //标准输出
    fputs(ch, stdout);
    //错误输出
    fputs(ch, stderr); 
    return 0;
}
