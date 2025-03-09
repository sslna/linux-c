#include <stdio.h>

int main(int argc, char const *argv[])
{
    fopen("bucunzai.txt","r");
    perror("打不开");
    return 0;
}
