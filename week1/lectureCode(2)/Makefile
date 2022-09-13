#rbt : brackets.o Stack.o
#	gcc -o rbt brackets.o Stack.o

#brackets.o : brackets.c Stack.h
#	gcc -Wall -Werror -c brackets.c

#Stack.o : Stack.c Stack.h
#	gcc -Wall -Werror -c Stack.c

#clean : 
#	rm -f *.o rbt 

CC=gcc    #(CC replaced by gcc)
CFLAGS=-Wall -Werror   #(c flags; W all and W error)

rbt : brackets.o Stack.o    										#[called a target; the target depends on the files given in :]
				gcc -Wall -Werror -o rbt brackets.o Stack.o

brackets.o : brackets.c Stack.h									#[target = brackets.o; files = brackets.c, brackets.h]
				$(CC) $(CFLAGS) -c brackets.c

Stack.o : Stack.c Stack.h
				$(CC) $(CFLAGS) -c Stack.c

clean :  																				#[remove all the executable so we can start from scratch]
				rm -f *.o rbt 