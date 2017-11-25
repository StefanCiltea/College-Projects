#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

struct thread_args
{
	int ln;
	int cl;
	int nrcol;
	int **a;
	int **b;
	int **c;
	
};

void *multiply(void *struc)
{
	struct thread_args args = *((struct thread_args *)struc);
	int* sum = (int*)malloc(4),i;
	*sum = 0;
	for (i = 0; i < args.nrcol; ++i)
		*sum+=(args.a[args.ln][i] * args.b[i][args.cl]);

	//args.c[args.ln][args.cl] = sum;

	return (void*)sum;
}

int main(int argc, char const *argv[])
{
	/* code */

	int **a1,**a2,**a3,n1,m1,n2,m2,i,j;

	/* Reading matrix 1 */
	scanf("%d",&n1);
	scanf("%d",&m1);

	a1 = (int **)malloc(n1*sizeof(int*));
	for (i = 0; i < n1; ++i)
	{
		a1[i] = (int*)malloc(m1*sizeof(int));
	}

	for (i = 0; i < n1; ++i)
		for(j = 0; j< m1; ++j)
			scanf("%d",(*(a1+i) + j));


	/* Reading matrix 2 */
	scanf("%d",&n2);
	scanf("%d",&m2);

	a2 = (int **)malloc(n2*sizeof(int*));
	for (i = 0; i < n2; ++i)
	{
		a2[i] = (int*)malloc(m2*sizeof(int));
	}

	for (i = 0; i < n2; ++i)
		for(j = 0; j< m2; ++j)
			scanf("%d",(*(a2+i) + j));

	/* Create matrix for result */
	a3 = (int **)malloc(n1*sizeof(int*));
	for (i = 0; i < n1; ++i)
	{
		a3[i] = (int*)malloc(m2*sizeof(int));
	}

	if(m1 != n2)
	{
		fprintf(stderr, "%s\n", "Matrices can't me multiplied because they are not compatible.\n" );
		return 1;
	}

	/* Array of threads */
	int thread_index = 0;
	pthread_t *threads = (pthread_t)malloc(n1*m2*sizeof(pthread_t)) ;
	struct thread_args *struc;
	void*exit_status;
	for (i = 0; i < n1; ++i)
	{
		for(j = 0; j < m2; ++j)
		{
			struc = (struct thread_args*)malloc(sizeof(struct thread_args));

			(*struc).ln = i;
			(*struc).cl = j;
			(*struc).nrcol = m1;
			(*struc).a = a1;
			(*struc).b = a2;
			(*struc).c = a3;

			if(pthread_create(threads+thread_index,NULL,multiply,struc))
			{
				// Create thread
				fprintf(stderr, "%s\n", "Error creating threads.\n" );
				return 2;
			}

			thread_index++;

		}
	
	}

	for (i = 0; i < n1; ++i)
	{
		for (j = 0; j < m2; ++j)
		{
			if(pthread_join(threads[i*m2+j],&exit_status ))
			{
				// Wait for thread to finish and colect data
				fprintf(stderr, "Error joining thread\n");
				return 3;
			}

			a3[i][j] = *((int*)exit_status);	// Set the result

		}
	}

	printf("%s\n","Result:" );

	for (i = 0; i < n1; ++i)
	{
		for(j = 0; j < m2; ++j)
		{
			printf("%d ", a3[i][j]);
		}
		printf("\n");
	}

	return 0;
}