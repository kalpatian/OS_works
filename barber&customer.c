#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <semaphore.h> 
#include <math.h>

#define MAX 10 
#define p(x) sem_wait(&x) 
#define v(x) sem_post(&x) 

sem_t customer,barber; 
int chairs; 
int waiting = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int if_no_more = 0;

void init ( )
{
    sem_init ( &customer , 0 , 0 ); //初始化customer 
    sem_init ( &barber , 0 , 1 );   //初始化barber 
    chairs = MAX;
}


void *_barber()		//理发师线程 
{
	while(1)
	{

		p(customer);
		pthread_mutex_lock(&mutex);
		chairs++;
		waiting--;
		pthread_mutex_unlock(&mutex);
		printf("haircut once!...\n");
		sleep(rand()%7+1);
		v(barber);
		sleep(rand()%2 + 1);
		if(if_no_more && waiting == 0)
        		break;
	}
	sleep(3);
	printf("barber go home to have a rest!\n");
	return;
 } 
void *_customer(void* arg)	//顾客线程 
{
 	int *p=(int*) arg;
 	int x;
 	x=*p;
 	pthread_mutex_lock(&mutex);
 	if(chairs>0)
 	{
 		chairs--;
 		
 		printf("the %dth customer get in the line,%d customer(s) is waiting...\n",x,MAX-chairs);
		pthread_mutex_unlock(&mutex);
		v(customer);
		p(barber); 
	 }
	else
	{
		printf("the %dth leave because the line is full...\n",x);
		pthread_mutex_unlock(&mutex);
	}
	return;
}

int main ( ) 
{
	int i; 
	srand(time(0));
	init ( ); 
	pthread_t b; 
	pthread_t pthreads[MAX]; 
	int cid[MAX]; 
	pthread_create ( &b , NULL , _barber , NULL ); 
	for ( i = 0 ; i < MAX ; i ++ ) 	//创建多个customer线程 
	{ 
		sleep(rand()%4 + 1); 
		cid[i] = i; 
		pthread_create ( &pthreads[i] , NULL , _customer , &cid[i] ); 
	} 
	
	if_no_more = 1;
	pthread_join ( b , NULL ); 		//运行barber线程 

	sem_destroy(&customer);
	sem_destroy(&barber);
	pthread_mutex_destroy(&mutex);
 
	return 0;
	
}

