#!/usr/bin/make
#
# Makefile for HelloWorld
#
# Author: TJR


hello: hello.o
	gcc hello.o -o hello

hello.o: hello.c
	gcc -c hello.c

clean:
	rm -f *~ *.o hello

run:
	./hello	
