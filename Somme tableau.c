#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#define tailleTableau 1000000

long sum=0;
pthread_mutex_t mutex;
long numberOfThreads = 0;
long tableau[tailleTableau];

void remplireTableau()
{
	for(int i=0; i<tailleTableau; i++)
	{
		tableau[i] = rand() % 40;
	}
}

void *SommePartielle (void *numThread)
{
	long num = (long) numThread;
	long nbIterations = (tailleTableau)/numberOfThreads;
	long indiceDebut = num * nbIterations;
	long sump = 0;	
	for(int i = indiceDebut ; i< indiceDebut + nbIterations; i++ )
	{
		sump+=tableau[i];
	}
	printf("Somme partielle du thread %d : %ld\n",getpid(),sump);
	pthread_mutex_lock(&mutex);
	sum+=sump;	
	pthread_mutex_unlock(&mutex)  ; 		
		
	pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
	int rc;
	numberOfThreads = strtol(argv[1], NULL, 10);
	remplireTableau();	
	pthread_t threads[numberOfThreads];
	for(long i = 0 ;i < numberOfThreads;i++)
	{
	        rc = pthread_create(&threads[i],NULL,SommePartielle,(void *) i);
        	if(rc!=0) printf("Creation  error on thread %ld\n",i);
		
	}      

	for(long i = 0 ;i < numberOfThreads;i++)
	{
		pthread_join(threads[i],NULL); 
	}
  	printf("\nLa somme est : %ld\n",sum);
	return 0;
}

