#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;

pthread_mutex_t mtx;

void* doThreadWork(void *arg)
{
	int amount = *((int *) arg);
	pthread_mutex_lock(&mtx);
	decrease_count(amount);	
	printf("Got %d resources,%d remaining\n",amount,available_resources);
	/* Relase now */
	pthread_mutex_unlock(&mtx);
	printf("Relased %d resources,%d remaining\n",amount,available_resources);
	pthread_mutex_lock(&mtx);
	increase_count(amount);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int decrease_count(int count)
{
	if(available_resources < count)
	{		
		return -1;
	}
	else
	{
		available_resources-=count;
		return 0;
	}
}

int increase_count(int count)
{	
	available_resources+=count;
}

int main()
{
	if(pthread_mutex_init(&mtx,NULL))
	{
		perror(NULL);
		return errno;
	}
	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*MAX_RESOURCES);

	int i;
	for(i=0;i<MAX_RESOURCES;i++)
	{
		int *arg = (int *)malloc(sizeof(int));
		*arg = i+1;
		if(pthread_create(threads+i,NULL,doThreadWork,(void*)arg))
		{
			return -1;
		}
		free(arg);
	}

	for(i=0;i<MAX_RESOURCES;i++)
	{
		if(pthread_join(threads[i],NULL))
		{
			perror(NULL);
			return errno;
		}
	}	
	
	pthread_mutex_destroy(&mtx);
	free(threads);
	return 0;
}
