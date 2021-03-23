CC=gcc
LIBS=-lpthread

all: boss-worker work-crew

boss-worker: boss-worker.c queue.c
		$(CC) boss-worker.c queue.c -o boss-worker $(LIBS)

work-crew: work-crew.c queue.c
		$(CC) work-crew.c queue.c -o work-crew $(LIBS)

clean:
	rm -rf *.o
	rm -rf boss-worker work-crew
