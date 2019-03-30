#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int buf[5],f,r;

sem_t mutex,full,empty;

void *producer(void *arg)
{
    int i;
    for(i=0;i<10;i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        printf("produced item is %d\n",i);
        buf[(++r)%5]=i;
        sleep(1);
        sem_post(&mutex);
                sem_post(&full);
        printf("full %u\n",full);
    }
}

void *consumer(void *arg)
{
    int item,i;
    for(i=0;i<10;i++)
    {
        sem_wait(&full);
    	printf("full %u\n",full);
        sem_wait(&mutex);
        item=buf[(++f)%5];
        printf("consumed item is %d\n",item);
        sleep(1);
        sem_post(&mutex);
        sem_post(&empty);
    }
}

main()
{
    pthread_t temp1,temp2;
    sem_init(&mutex,0,1);
    sem_init(&full,0,1);
    sem_init(&empty,0,5);
    pthread_create(&temp1,NULL,producer,NULL);
    pthread_create(&temp2,NULL,consumer,NULL);
    pthread_join(temp1,NULL);
    pthread_join(temp2,NULL);
}