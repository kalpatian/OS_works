#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <semaphore.h> 
#include <math.h>

#define p(x) sem_wait(&x) 
#define v(x) sem_post(&x) 

sem_t chops[5];
sem_t mutex;
int seat[5] = {0, 0, 0, 0, 0};

void init();            // initialize the semaphore of chops 
void *philo(void *arg); // what about the philosophers

int main()
{
	srand((unsigned int)(time(NULL)));
    init();
    pthread_t philosopher[5];
    for(int i = 0; i < 20; i++)
    {
    	sleep(rand()%7+1);
        pthread_create(&philosopher[i], NULL, philo, NULL);
    }
    
    return 0;
}


void init()
{
    for (int i = 0; i < 5; i++)
        sem_init (&chops[i] , 0 , 1);  
}


void *philo(void *arg)
{
    srand(time(0));
    int i = rand()%5;

    if (!seat[i] && !seat[(i+1)%5] && !seat[(i+4)%5])
    {
        seat[i] = 1;
        p(chops[i]);
        p(chops[(i+1)%5]);
        sleep(rand()%2+1);
        printf("now philo no.%d is dining.\n", i);
        v(chops[i]);
        v(chops[(i+1)%5]);
        seat[i] = 0;
        printf("now philo no.%d is thinking.\n", i);
    }
}
