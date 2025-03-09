# 经常使用到的gcc编译格式
CC:=gcc

fopen_test: fopen_test.c 
#gcc -o fopen_test fopen_test.c
	-$(CC) -o $@ $^
#./fopen_test
	-./$@
#rm ./fopen_test
	-rm ./$@

fclose_test: fclose_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fputc_test: fputc_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fputs_test: fputs_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fprint_test: fprintf_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fgetc_test: fgetc_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fgets_test: fgets_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fscanf_test: fscanf_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

stdin_out_err_test: stdin_out_err_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unistd_test: unistd_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

system_call_test: system_call_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

system_call: system_call.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@