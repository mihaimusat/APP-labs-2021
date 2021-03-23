CC=gcc
CFLAGS=-Wall -lm -fopenmp

.PHONY: clean all

all: ex1 ex2

ex1: ex1.c
	$(CC) $? -o $@ $(CFLAGS)

ex2: ex2.c
	$(CC) $? -o $@ $(CFLAGS)

clean:
	rm -f ex1 ex2
