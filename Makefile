CC=gcc
CFLAGS= -Wall -Werror -ggdb

default: main

all: bnum main 

main: main.c
	$(CC) $(CFLAGS) main.c bnum.o -o factorial 

bnum: bnum.c 
	$(CC) $(CFLAGS) -c bnum.c

clean:
	$(RM) factorial

