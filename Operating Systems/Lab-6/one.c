#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

void *handleString(void *s)
{
	char aux;
	int i,length;
	char *str = (char *)s;
	length = strlen(str);
	for(i=0;i<length/2;i++)
	{
		aux = str[i];
		str[i] = str[length - 1 - i];
		str[length - 1 - i] = aux;
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		pthread_t myThread;

		char*str = (char*)malloc(strlen(argv[1]));
		strcpy(str,argv[1]);

		if(pthread_create(&myThread, NULL,handleString, str))
		{
			fprintf(stderr,"Error creating thread.\n" );
			return 1;
		}

		/* wait for the second thread to finish */
		if(pthread_join(myThread, NULL)) {

			fprintf(stderr, "Error joining thread\n");
			return 2;
		}

		printf("%s\n",str);
		return 0;

	}

	fprintf(stderr, "Invalid number of arguments in argv.\n");
	return 3;
	

}