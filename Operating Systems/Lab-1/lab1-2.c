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
  pid_t pid = fork();

  if(pid < 0)
     return;
  else if(pid == 0)
  {
  	 int n;
  	 scanf("%d",&n);
     recursiveFunc(n);
  }
  else
  {
  	wait();
    printf("\nChild finished.\n");
  }

  return 0;
}