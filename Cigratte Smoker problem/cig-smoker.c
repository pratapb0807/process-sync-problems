#include<stdio.h> 
#include<sys/types.h> 
#include<semaphore.h> 
#include<pthread.h> 

int table_used=1,generated_item[2],generated=0; 
char *item[]={"tubaco","paper","matches"}; 

sem_t table;

void *agent(void *arg) { 
	int i,j,k=0; 
	while(1)       
	{
		sleep(1);
		sem_wait(&table); 
		if(table_used==1)             
			{ 
				i=k; 
				j=i+1; 
				if(j==3) 
					j=0; 
				k=j; 
				generated_item[0]=i; 
				generated_item[1]=j; 
				printf("agent is prodused %s,%s\n",item[i],item[j]); 
				generated=1; 
				table_used=0;
           } 
		sem_post(&table);
	} 
}

void  *smoker(int i) { 
	while(1)       
	{ 
		sleep(1); 
		sem_wait(&table); 
		if(table_used==0)             
		{ 
			if(generated && generated_item[0]!=i && generated_item[1]!=i)                  
			{ 
				printf("smoker%d completed his smoking\n",i);
				table_used=1; 
				generated=0;
			}             
		} 
		sem_post(&table);       
	} 
}

void main() { 
	pthread_t smkr0,smkr1,smkr2,agnt; 
	sem_init(&table,0,1);
	pthread_create(&agnt,0,agent,0); 
	pthread_create(&smkr0,0,smoker,0); 
	pthread_create(&smkr1,0,smoker,1); 
	pthread_create(&smkr2,0,smoker,2); 
	while(1);  
} 
