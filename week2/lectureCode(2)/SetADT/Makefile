# Makefile for Set ADT

CC = gcc
CFLAGS = -Wall -Werror -g

all : ts 

ts : testSet.o Set.o
	$(CC) -o ts testSet.o Set.o

testSet.o : testSet.c Set.h
	$(CC) $(CFLAGS) -c testSet.c

Set.o : Set.c Set.h Bool.h

clean :
	rm -f *.o  ts core

