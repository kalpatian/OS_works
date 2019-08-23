#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>



void *monitor_input(void *p) // thread 02
{
    int number = 0;
    pthread_t *tid2=pthread_self(); 
    int i = 0;
    int setin=0;
    char ch[100];
    printf("please input a word!:\n");
    scanf("%s",ch);
    while (i < 100)
    {
        if (ch[i] == '\0') 
        {
            number = atoi(ch);
            break;
        }
        if (ch[i] >= '0' && ch[i] <= '9')
        {
            i++;
        }
        else if (ch[i] == 'p')
        {
            number = -1;
            break;
        }
        else if (ch[i] == 'e')
        {
            number = -2;
            break;
        }
        else
        {
            number = -3;
            break;
        }
       
    }
    pthread_exit(&number);

} 

void *summing(int *args)    // thread 01
{
    pthread_t *tid1=pthread_self(); 
    int sum =0;
    int number=*args;
    if (number == -1)
    {
        printf("error code -1\n");
        pthread_exit(NULL);
    }
    else if (number == -2)
    {
        printf("error code -2\n");
    }
    else if (number == -3)
    {
        printf("error code -3\n");
    }

    else if (number > 0 )
    {
        sum = (1 + number)*number/2;
    }
    printf("the sum is %d\n",sum);
}


int main(void){
	pid_t fpid;
	fpid=fork();
	if(fpid<0)
		{
		printf("fork error!\n");
		}//unsuccessful fork!
	else if(fpid==0)
		{
		int num2=0;
    		int* pi=NULL;
    		pthread_t tid1;
    		pthread_t tid2;

    		pthread_create(&tid2,NULL,monitor_input,NULL);
    		pthread_join(tid2, (void**)&pi); //pi=number

    		pthread_create(&tid1,NULL,summing,pi);
    		pthread_join(tid1, NULL);
		printf("please input number2:\n");
		scanf("%d",&num2);
		if(num2!=*pi)
			{
			pthread_create(&tid1,NULL,summing,&num2);
			pthread_join(tid1,NULL);
			}


		}//son process (sum 1~x)
	else
		{
		printf("hello world!\n");
		wait(NULL);

		}//father process(print :HELLO WORLD)
}
