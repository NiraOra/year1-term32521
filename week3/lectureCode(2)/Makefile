## trial makefile ??

CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

.PHONY: all
all: ex1

ex1: ex1.o
  $(CC) $(CFLAGS) -o ex1 ex1.o
#ex2 : ex2.o
#  $(CC) $(CFLAGS) -o ex2 ex2.o
#ex3 : ex3.o
#  $(CC) $(CFLAGS) -o ex3 ex3.o

ex1.o : ex1.c
#ex2.o: ex2.c
#ex3.o: ex3.c

.PHONY: clean

clean:
  rm -f ex1 *.o