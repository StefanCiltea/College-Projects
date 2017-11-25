#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <sys/mman.h>

void Collatz(int n,char *shm_ptr)
{
	int offset = sprintf(shm_ptr,"%d ",n);
	shm_ptr+=offset;

	if(n>1)
	{
		if(n%2 == 0)
			Collatz(n/2,shm_ptr);
		else 
			Collatz(3*n+1,shm_ptr);
	}
}

int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		perror("Insuficiente argumente.\n");
		return errno;
	}
	char shm_name[] = "myshm";
	int shm_fd;	
	int shm_size = getpagesize() * argc;
	int page_size = getpagesize();
	int i,pid;

	shm_fd=shm_open(shm_name,O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);

	if(shm_fd < 0)
	{
		perror(NULL);
		return errno;
	}

	if(ftruncate(shm_fd,shm_size)==-1)
	{
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	} 


	printf("%s\n","Starting parent.");
	for(i=1;i<argc;i++)
	{
		pid = fork();	/*Create child*/
		if(pid<0)
		{
			perror(NULL);
			shm_unlink(shm_name);
			return errno;
		}
		else if(pid == 0)
		{
			/*Child code*/

			void* shm_ptr = mmap(NULL,page_size,PROT_WRITE|PROT_READ,MAP_SHARED,shm_fd,i*page_size);
			if(shm_ptr == MAP_FAILED)
			{

				perror(NULL);
				shm_unlink(shm_name);
				return errno;
			}
			
			Collatz(atoi(argv[i]),(char*)shm_ptr);
			printf("Done parent:%d me: %d\n",getppid(),getpid());
			munmap(shm_ptr,page_size);
			exit(0);
		} 
		else
		{
			/*Parent code*/
			wait(NULL);
		}
		
	}

	printf("Childs finished.\n");

	for(i = 1;i<argc;i++)
	{
		void* shm_ptr = mmap(NULL,page_size,PROT_WRITE|PROT_READ,MAP_SHARED,shm_fd,i*page_size);
		if(shm_ptr == MAP_FAILED)
		{
			perror(NULL);
			shm_unlink(shm_name);
			return errno;
		}
		printf("%d : %s\n",atoi(argv[i]),(char*)shm_ptr);
		munmap(shm_ptr,page_size);
	}
	

	printf("Done Parent:%d , Me:%d\n",getppid(),getpid());

	return 0;
}
