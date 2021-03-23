/* example structure for the Boss-Worker parallel programming model
 * see Thread Time: The Multithreaded Programming Guide
 * Scott J.Norton and Mark D.DiPasquale
 * 1997, Prentice Hall (www.prenhall.com)
 * ISBN: 0-13-190067-6
 * adapted by Bogdan Costinescu, march 1999
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <malloc.h>
#include <pthread.h>

#include "queue.h"

#define NMAX 10

/* global queue */
extern struct queue_struct thr_queue;
int a[NMAX][NMAX], b[NMAX][NMAX], c[NMAX][NMAX];

void check_error(int code, char *generator) {

}

int
queue_terminate_workers(struct queue_struct *queue) 
{
  if ((queue == NULL) || (queue->valid != QUEUE_VALID))
    return EINVAL;
  
  (void) pthread_mutex_lock(&queue->qlock);
  queue->qexit = 1;

  /* wakeup any waiting workers */
  (void) pthread_cond_broadcast(&queue->worker_cv);
  (void) pthread_mutex_unlock(&queue->qlock);

  return 0;
}

void 
queue_wait_workers(struct queue_struct *queue, int nthreads)
{
  if ((queue == NULL) || (queue->valid != QUEUE_VALID))
    return;
  
  (void) pthread_mutex_lock(&queue->qlock);
  while (queue->worker_waiting != nthreads) {
    queue->boss_waiting++;
    (void) pthread_cond_wait(&queue->boss_cv, &queue->qlock);
    queue->boss_waiting--;
  }
  (void) pthread_mutex_unlock(&queue->qlock);
}

int optimal_number_of_threads(void) {
	return 4;
}

int optimal_queue_length(void) {
	return 8;
}

void
process_tasks()
{
#define MAX_THREADS 64
  int i, ret, nthreads, max_queue_len;
  pthread_t threads[MAX_THREADS];
  pthread_attr_t attr;
  void worker(), boss();

  /* initialization code */
  /* ... */

  /* determine the number of threads to create and max queue length */
  nthreads = optimal_number_of_threads();
  max_queue_len = optimal_queue_length();

  /* initialize the queue */
  if ( queue_init(&thr_queue, max_queue_len) != 0 ) {
    fprintf(stderr, "queue_init() error\n");
    exit(-1);
  }

  /* initialize any special thread attributes (if needed) */
  (void) pthread_attr_init(&attr);
  /* ... */

  /* create worker threads */
  for (i = 1; (i < nthreads) && (i < MAX_THREADS); i++) {
    ret = pthread_create(&threads[i],
			 &attr,
			 (void *(*)())worker,
			 NULL);
    check_error(ret, "pthread_create()");
  }
  (void) pthread_attr_destroy(&attr);

  /* we are in the boss thread */
  boss();

  /* request the workers terminate when all work is processed */
  if ( queue_terminate_workers(&thr_queue) != 0 ) {
    fprintf(stderr, "dequeue() error\n");
    exit(-1);
  }

  /* wait for the workers to terminate */
  for (i = 1; (i < nthreads) && (i < MAX_THREADS); i++) {
    ret = pthread_join(threads[i], NULL);
    check_error(ret, "pthread_join()");
  }

  /* perform any final processing and return */
}

int get_work(struct q_work_struct* w, int i) {
	
	w->column = i;
  	if(i == NMAX) { 
    		return 0;
	}
  	else {
    		return 1;
	}
}

void
boss()
{
  struct q_work_struct *ptr;
  int i = 0, ret;
  
  /* obtain work, return when complete */
  for ( ; ; ) {
    /* allocate a work structure */
    ptr = (struct q_work_struct *) malloc (sizeof(struct q_work_struct));
    if ( ptr == NULL )
      break;
    
    /* create/obtain work and fill in the work structure */
    ret = get_work(ptr, i);
    if ( ret == 0 ) {
      free((void *)ptr);
      break;
    }

    /* queue up the work */
    if ( enqueue(&thr_queue, ptr) != 0 ) {
      fprintf(stderr, "enqueue() error\n");
      exit(-1);
    }
    i += NMAX;
  }
}

void
worker()
{
  struct q_work_struct *ptr;
  int i;
  
  /* go into an infinite loop processing work received from
   * the work queue. If we are supposed to terminate, we
   * will never return from one of the calls to dequeue();
   */
  for ( ; ; ) {
    /* obtain the next work request */
    ptr = dequeue(&thr_queue);
    if ( ptr == NULL ) {
      fprintf(stderr, "dequeue() error\n");
      exit(-1);
    }
    
    /* process the work request */
    /* ... */
    int col = ptr->column;
    for(i = 0; i < NMAX; i++) {
	c[i][col] = a[i][col] + b[i][col];
    }

    /* release memory for work request */
    free((void *)ptr);
  }
}

int main() 
{  
	int i, j;
  	for(i = 0; i < NMAX; i++) {
		for(j = 0; j < NMAX; j++) {
    			a[i][j] = b[i][j] = NMAX * i + j;
    			c[i][j] = 0;
  		}
	}

  	process_tasks();

	printf("First matrix is: \n");
  	for(i = 0; i < NMAX; i++) {
		for(j = 0; j < NMAX; j++) {
    			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

  	printf("\n");

	printf("Second matrix is: \n");
  	for(i = 0; i < NMAX; i++) {
		for(j = 0; j < NMAX; j++) {
    			printf("%d ", b[i][j]);
		}
		printf("\n");
	}

  	printf("\n");
	
	printf("Sum of elements from first column is: \n");
  	for(i = 0; i < NMAX; i++) {
		for(j = 0; j < NMAX; j++) {
    			printf("%d ", c[i][j]);
		}
		printf("\n");
	}

  	printf("\n");

  	return 0;
}
