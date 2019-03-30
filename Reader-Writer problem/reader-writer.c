#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,wrBlock;
int data = 0;
int rdcount = 0;

void *reader(void *arg)
{
  int temp;
  temp = ((int)arg);
  sem_wait(&mutex);
  rdcount = rdcount + 1;
  if(rdcount==1)
   sem_wait(&wrBlock);
  sem_post(&mutex);
  printf("Data read by the reader%d is %d\n",temp,data);
  sleep(1);
  sem_wait(&mutex);
  rdcount = rdcount - 1;
  if(rdcount==0)
   sem_post(&wrBlock);
  sem_post(&mutex);
}

void *writer(void *arg)
{
  int temp;
  temp = ((int) arg);
  sem_wait(&wrBlock);
  data++;
  printf("Data writen by the writer%d is %d\n",temp,data);
  sleep(1);
  sem_post(&wrBlock);
}

main()
{
  int i,b; 
  pthread_t rd_tid[5],wr_tid[5];
  sem_init(&mutex,0,1);
  sem_init(&wrBlock,0,1);
  for(i=0;i<=2;i++)
  {
    pthread_create(&wr_tid[i],NULL,writer,(void *)i);
    pthread_create(&rtid[i],NULL,reader,(void *)i);
  }
  for(i=0;i<=2;i++)
  {
    pthread_join(wr_tid[i],NULL);
    pthread_join(rd_tid[i],NULL);
  }
}