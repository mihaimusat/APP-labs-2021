CC=gcc
CFLAGS=-Wall -lm -fopenmp

.PHONY: clean all

all: matrix_mult ex1 ex2

matrix_mult: matrix_mult.c
	$(CC) $? -o $@ $(CFLAGS)

ex1: ex1.c
	$(CC) $? -o $@ $(CFLAGS)

ex2: ex2.c
	$(CC) $? -o $@ $(CFLAGS)

clean:
	rm -f matrix_mult ex1 ex2
