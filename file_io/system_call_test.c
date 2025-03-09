#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    //打开文件
    int fd = open("io.txt", O_RDONLY);
    if (fd==-1)
    {
        printf("打开失败");
        exit(1);
    }

    char buffer[1024];//用于存放读取的数据
    ssize_t bytes_read;
    /**
     * ssize_t read (int __fd, void *__buf, size_t __nbytes)
     * int __fd     文件描述符
     * void *__buf  存放数据
     * size_t __nbytes  读取数据的长度
     * return:ssize_t（即为long int）读取到数据的字节长度 成功大于0 失败-1
     */
    while ((bytes_read=read(fd,buffer,sizeof(buffer)))>0)
    {
        /**
         *  #define	STDIN_FILENO	0	/* Standard input. 
          #define	STDOUT_FILENO	1	/* Standard output.  
            #define	STDERR_FILENO	2	/* Standard error output. 
        */

        /**
         * ssize_t write (int __fd, const void *__buf, size_t __n)
         * int __fd 文件描述符
         * const void *__buf    要写出的数据
         * size_t __n   写出的长度
         * return 成功返回写出数据的长度，失败返回-1
         */
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read==-1)
    {
        printf("读取文件失败\n");
        close(fd);
        exit(1);
    }
    close(fd);

    return 0;
}
