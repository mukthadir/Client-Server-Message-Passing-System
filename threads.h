#include<stdlib.h>
#include "q.h"

#define STACK_SIZE 8192

void start_thread(void (*funciton) (void))
{
	void* stackP = (void*) malloc(STACK_SIZE);
	struct TCB_t *tcb = (struct TCB_t *)malloc(sizeof(struct TCB_t));
	init_TCB(tcb, funciton, stackP, STACK_SIZE);
	AddQ(&runQ, tcb); 
}

void run()

{   // real code

    ucontext_t parent;     // get a place to store the main context, for faking

    getcontext(&parent);   // magic sauce

    swapcontext(&parent, &(runQ->context));  // start the first thread
}

void yield()
{
	ucontext_t parent;
	getcontext(&parent);
	runQ->context = parent;
	RotateQ(&runQ);
	swapcontext(&parent, &(runQ->context));
}
