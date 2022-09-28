## check why leak is not defined

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,undefined

.PHONY: all
all: code

code: CodeRun.o 
	$(CC) $(CFLAGS) -o code CodeRun.o

CodeRun.o: CodeRun.c CodeRun.h

.PHONY: clean
clean:
	rm -f CodeRun *.o
