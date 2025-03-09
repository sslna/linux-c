CC :=gcc

system_test:system_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_test:fork_test.c 
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_fd_test:fork_fd_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

erlou:erlou.c
	-$(CC) -o $@ $^

execve_test:execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

perror_test:perror_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unanamed_pipe_test:unanamed_pipe_test.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@

fifo_write:fifo_write.c
	-$(CC) -o $@ $^

fifo_read:fifo_read.c
	-$(CC) -o $@ $^

shared_memory:shared_memory.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

father_son_mq_test:father_son_mq_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

producer:producer.c
	-$(CC) -o $@ $^

consumer:consumer.c
	-$(CC) -o $@ $^

signal_test:signal_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@