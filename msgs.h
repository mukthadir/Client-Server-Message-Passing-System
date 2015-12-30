#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include "sem.h"

#define num_port 100
#define msg_size 11
#define num_msg 10

typedef struct port_t					//Step 1.
{
	int in, out;					//No. of msgs in the port.
	int msgArr[num_msg][msg_size];

	struct Semaphore_t *semPortFull;
	struct Semaphore_t *semPortEmpty;
	struct Semaphore_t *semPortMutex;
}port_t;

struct port_t portArr[num_port];

void createPort()				//Initialising a port.
{	
	int port_num;
	for( port_num=0; port_num<100; port_num++)
	{
		portArr[port_num].in = 0;
		portArr[port_num].out = 0;
		portArr[port_num].semPortFull = CreateSem(0);
		portArr[port_num].semPortEmpty = CreateSem(10);
		portArr[port_num].semPortMutex = CreateSem(1);
	}
}



void send(int port_num, int *msg)
{
	int i, *msgs;
//	msgs = (int *)malloc(sizeof(int) * 10);
//	msgs = (int *)msg;
	P(portArr[port_num].semPortEmpty);
	P(portArr[port_num].semPortMutex);

		for(i = 0; i < msg_size; i++)
		{
			portArr[port_num].msgArr[portArr[port_num].in][i] = msg[i];
		}
		portArr[port_num].in =	(portArr[port_num].in + 1) % 10;
		
	V(portArr[port_num].semPortMutex);
	V(portArr[port_num].semPortFull);

}

void recv(int port_num, int *msg)
{
	int i, *msgs;
//	msgs = (int *)malloc(sizeof(int) * 10);
//	msgs = (int *)msg;
	P(portArr[port_num].semPortFull);
	P(portArr[port_num].semPortMutex);

		for(i = 0; i <= msg_size; i++)
		{
			msg[i] = portArr[port_num].msgArr[portArr[port_num].out][i];
		}
		portArr[port_num].out =	(portArr[port_num].out + 1) % 10;
	
	
		
	V(portArr[port_num].semPortMutex);
	V(portArr[port_num].semPortEmpty);
	
}


