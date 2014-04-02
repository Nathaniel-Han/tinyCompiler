#
# makefile for tinyCompiler
#

CC = g++

CFLAGS =

OBJS = dlist.o stack.o Lex.o Syntax.o main.o

tinyComipler: $(OBJS)
	$(CC) $(CFLAGS) -o tinyCompiler $(OBJS)

dlist.o: 
	$(CC) $(CFLAGS) -c dlist.c

stack.o:
	$(CC) $(CFLAGS) -c stack.c
	
Lex.o:
	$(CC) $(CFLAGS) -c Lex.cpp
	
Syntax.o: global.h
	$(CC) $(CFLAGS) -c Syntax.cpp

main.o:
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -rf *.o
	rm -rf tinyCompiler
	
