#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#define tailleTableau 32751

pthread_mutex_t mutex;
long tableau1[tailleTableau];
long tableau2[tailleTableau];
long sum[tailleTableau];

void remplireTableaux()
{
	for(int i=0; i<tailleTableau; i++)
	{
		tableau1[i] = rand() % 40;
		tableau2[i] = rand() % 50;
	}
}

void *SommePartielle (void *indice)
{
	long ind = (long) indice;	 		
	sum[ind] = tableau1[ind] + tableau2[ind];
	pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
	int rc;
	remplireTableaux();
	pthread_t threads[tailleTableau];

	for(long i = 0 ;i < tailleTableau;i++)
	{
	        rc = pthread_create(&threads[i],NULL,SommePartielle,(void *) i);
        	if(rc!=0) printf("Creation  error on thread %ld\n",i);
		
	}      

	for(long i = 0 ;i < tailleTableau;i++)
	{
		pthread_join(threads[i],NULL); 
	}
	return 0;
}

