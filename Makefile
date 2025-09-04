# Makefile for prime number fun

# $Id: Makefile,v 1.1 2025/03/30 02:06:31 scott Exp scott $

CFLAGS = -O

# TODO: how to build prime.`arch`.x or make a combined image
# TODO: my makefile knowledge is rusty!  
prime.x: prime.o
	$(CC) $(CFLAGS) -o prime.x prime.o

clean:
	rm prime.x prime.o
