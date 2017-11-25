#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_THR 5

pthread_mutex_t mtx;
sem_t sem;
int count = 0;
int relase_state=0;

void barrier_point()
{
	pthread_mutex_lock(&mtx);
	count++;
	pthread_mutex_unlock(&mtx);
	
	if(count < MAX_THR && sem_wait(&sem))
	{
		perror(NULL);
		exit(0);
	}

	relase_state = 1;	/* Dam drumul thread-urilor */

	if(relase_state)
	{
		if(sem_post(&sem))
		{
			perror(NULL);
			exit(0);
		}
	}
}

void* doThreadWork(void *arg)
{
	int threadid = *((int *) arg);
	
	printf("%d reached the barrier\n",threadid);
	barrier_point();	

	/* Relase now */
	printf("%d passed the barrier\n",threadid);
	
	
	return NULL;
}

int main()
{
	if(pthread_mutex_init(&mtx,NULL))
	{
		perror(NULL);
		return errno;
	}

	if(sem_init(&sem,0,0))
	{
		perror(NULL);
		return errno;
	}

	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*MAX_THR);

	int i;
	for(i=0;i<MAX_THR;i++)
	{
		int *arg = (int *)malloc(sizeof(int));
		*arg = i;
		if(pthread_create(threads+i,NULL,doThreadWork,(void*)arg))
		{
			return -1;
		}
	}

	for(i=0;i<MAX_THR;i++)
	{
		if(pthread_join(threads[i],NULL))
		{
			perror(NULL);
			return errno;
		}
	}	
	
	pthread_mutex_destroy(&mtx);
	sem_destroy(&sem);
	free(threads);
	return 0;
}
