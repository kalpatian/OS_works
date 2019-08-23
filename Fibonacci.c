#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/shm.h>
#define MAX_SEQUENCE 20

typedef struct{
	long fib_sequence[MAX_SEQUENCE];
	int sequence_size; 
}shared;

int main(void){
	int SIZE=sizeof(shared);
	int shmid;
	void *shm_addr;
	shared *sharepart;
	shmid=shmget(IPC_PRIVATE,SIZE,(SHM_R|SHM_W|IPC_CREAT));
	shm_addr=shmat(shmid,NULL,0);
	sharepart=(shared*)shm_addr;
	pid_t fpid;
	int input;
	printf("please input a number as the information to the Fibonacci:\n");
	scanf("%d",&input);

	fpid=fork();
	if(fpid<0)
		{
		printf("fork error!\n");
		}//unsuccessful fork!
	else if(fpid==0)
		{
		
    	sharepart->fib_sequence[0]=0;
    	sharepart->fib_sequence[1]=1;
    	sharepart->fib_sequence[2]=1;
    	for(int i=3;i<sharepart->sequence_size;i++)
        	{	
		(sharepart->fib_sequence[i])=sharepart->fib_sequence[i-1]+sharepart->fib_sequence[i-2];
		}
		shmdt(shm_addr);
	exit(0);
		}//son process
	else
		{
		
		if(input<=MAX_SEQUENCE&&input>=0){
			sharepart->sequence_size=input;
			wait(NULL);
			printf("the Fibonacci is ");
			int i;
			for(i=1;i<sharepart->sequence_size;i++)
			{
				printf("%ld,",sharepart->fib_sequence[i]);
			}
			shmctl(shmid,IPC_RMID,NULL);
			exit(0);
			}
		else
			{
			printf("error input!\n");
			return 0;
			}
		}//father process
}
