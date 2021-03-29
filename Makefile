CC=gcc
CFLAGS= -Wall -Werror -ggdb

default: all
all: bnum

bnum: main.c
	$(CC) $(CFLAGS) -o a.out main.c

clean veryclean:
	$(RM) a.out

