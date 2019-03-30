#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t customers;
sem_t barber;
sem_t access_seats;

int number_of_free_seats = 25;
int total_customers = 5;

void customer(int number)
{
  for (;;) {
    printf("[PID %d] Customer %d: Trying to access seat.\n",
	   getpid(), number);
    sem_wait(&access_seats);
    printf("[PID %d] Customer %d: Checking if any free seats.\n",
	   getpid(), number);
    if (number_of_free_seats > 0) {
      printf("Customer %d sat down in waiting room. [PID: %d]\n",
	     number, getpid());
      number_of_free_seats--;
      sem_post(&customers);
      sem_post(&access_seats);
      sem_wait(&barber);
    }
    else {
      sem_post(&access_seats);
      printf("Customer %d left (no free seats).\n", number);
    }
  }
}

void barber()
{
  for (;;) {
    printf("Barber is ready for customer.\n");
    sem_wait(&customers);
    printf("Barder is trying to access seats\n");
    sem_wait(&access_seats);
    number_of_free_seats++;
    printf("Barber is ready to cut.\n");
    sem_post(&barber);
    sem_post(&access_seats);
    printf("Barber is cutting hair");
  }
}

int main()
{
  sem_init(&customers, 0,1);
  sem_init(&barber, 0,1);
  sem_init(&access_seats, 1,1);
  int i;
  for (i = 0; i < total_customers; i++) {
    if(fork() == 0) {
      printf("Fork!\n");
      customer(i);
      exit(0);
    }
  }
  barber();
  return 0;
}