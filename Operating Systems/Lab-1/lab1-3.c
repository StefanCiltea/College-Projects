#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

void recursiveFunc(int n)
{
	printf("%d ",n);
	if(n != 1)
	{
		if(n%2 == 0)
		{
			recursiveFunc(n/2);
		}
		else
		{
			recursiveFunc(3*n+1);
		}
	}
}

int main()
{
  int n,idx = 0;
  scanf("%d",&n);
  
  int *v = (int*)malloc(sizeof(int)*n);
  pid_t *pids = (pid_t*)malloc(sizeof(pid_t)*n);
 
  int i;

  /* Start children. */
  for (i = 0; i < n; ++i) {
    pid=fork();
    switch(pid)
    {
        case 0:
        {
            cout<<"\nI am a child and my pid is:"<<getpid();
            cout<<endl;
            exit(0);
            break;
        }
        default:
        {
            cout<<"\nI am a parent and my pid is: "<<getpid();
            cout<<"\nMy child pid is: "<<pid;
            cout<<endl;
            wait(NULL);
            break;
        }
    }
  }


  return 0;
}