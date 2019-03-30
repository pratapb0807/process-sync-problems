#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t stick[5];

void* philosopher(void* j)
{
 int i =(int) j;
 printf("Philosopher %d is Hungry\n",i);
 sem_wait(&stick[(i+1)%5]);
 sem_wait(&stick[(i+5)%5]);
 printf("Philosopher %d is eating\n",i);
 sleep(1);
 sem_post(&stick[(i+1)%5]);
 sem_post(&stick[(i+5)%5]);
 printf("Philosopher %d is thinking\n",i);
}

void main()
{
 int i;
 pthread_t pid[5];
 for(i=0;i<5;i++)
 sem_init(&stick[i],0,1);
 for(i=0;i<5;i++)
  pthread_create(&pid[i],NULL,philosopher,(void*)i);
  for(i=0;i<5;i++)
  pthread_join(pid[i],NULL);
}