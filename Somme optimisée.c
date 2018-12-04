#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#define nbIteration 1000000

long sum=0;
pthread_mutex_t mutex;

void *print (void *numThread)
{
	long num = (long) numThread;
	printf("With getpid() : %d\n", getpid());
	printf("With self() : %p\n", (void *)pthread_self());
	printf("Numéro d'ordre : %ld\n", num);
	long sump = 0;	
	for(int i = 0 ; i< nbIteration;i++)
	{
		sump+=num;
	}
	pthread_mutex_lock(&mutex);
	sum+=sump;	
	pthread_mutex_unlock(&mutex)  ; 		
		
	pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
	int rc;
	long num = strtol(argv[1], NULL, 10);
	pthread_t threads[num];
	for(long i = 0 ;i < num;i++)
	{
		//printf("Creating Thread %ld\n", i); 
	        rc = pthread_create(&threads[i],NULL,print,(void *) i);
        	if(rc!=0) printf("Creation  error on thread %ld\n",i);
		
	}      
	for(long i = 0 ;i < num;i++)
	{
		pthread_join(threads[i],NULL); 
	}
  	printf("\nLa somme est : %ld\n",sum);
	return 0;
}

