#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include "threads.h"

typedef struct Semaphore_t{
	int sem_count;		//Semaphore queue.
	TCB_t *SemQ;		//Semaphore queue.
}Semaphore_t;

Semaphore_t* CreateSem(int in_val){
	Semaphore_t *sem = (Semaphore_t *)malloc(sizeof(struct Semaphore_t));
	sem->sem_count = in_val;
	InitQ(&sem->SemQ);
	return sem;
}

void P(Semaphore_t *sem){
	sem->sem_count--;
	if(sem->sem_count < 0){
			TCB_t *tmp = DelQ(&runQ);
	
			AddQ(&(sem->SemQ), tmp);	//Adding to the semQ.

			swapcontext(&(tmp->context), &(runQ->context));	//Swapping the context.
		}
	
}
void V(Semaphore_t *sem){
	sem->sem_count++;
	if(sem->sem_count <= 0){
			TCB_t *tmp = DelQ(&(sem->SemQ));	//Deleting from the semQ.
			AddQ(&runQ, tmp);	
		}
	yield();
		
}


