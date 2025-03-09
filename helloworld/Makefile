# Makefile内容通常由3部分组成
# <目标名词>:<前置依赖>
#	\t<需要执行的命令>

# 定义变量 objects
objects := hello.o main.o
# \ 为换行

# 放在第一个的是默认目标
# 目标是编译出main文件 依赖hello.o和main.o文件
# 编译的命令是gcc hello.o main.o -o main
main:$(objects)
	gcc hello.o main.o -o main

# 目标是main.o
# main.o:main.c hello.h
# 	gcc -c main.c -o main.o

#makefile的自动推导功能，只需写出它无法监测到的文件
main.o:hello.h


#目标是hello.o
# hello.o:hello.c hello.h
# 	gcc -c hello.c
hello.o: hello.h


#声明伪目标
.PHONY: clean
#忽略错误 在代码前加-
clean:
	-rm $(objects) 