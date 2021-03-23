CC=gcc
CFLAGS=-Wall -lm -fopenmp

.PHONY: clean all

all: bug2 bug3 bug6

bug2: bug2.c
	$(CC) $? -o $@ $(CFLAGS)

bug3: bug3.c
	$(CC) $? -o $@ $(CFLAGS)

bug6: bug6.c
	$(CC) $? -o $@ $(CFLAGS)

clean:
	rm -f bug2 bug3 bug6
