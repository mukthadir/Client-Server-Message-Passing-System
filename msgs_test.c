/*****************************

DMOS Project 3

Submitted by -

Saurabh Satija 	     1206252485

Mukthadir Choudhury  1207597049


********************************/

	
#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include<time.h>
#include "msgs.h"


int count = 1;
int client_id = 0;

int arr[10] = {7, 6, 3, 1, 0, 5, 2, 9, 4, 8};

Semaphore_t *lock;

void client(void)
{
	int recv_arr[11], c_arr[11], i, x;
		P(lock);
		x = client_id++;
		V(lock);
	while(1){
		
		
		c_arr[0] = x;
		for(i = 0; i < 10; i++)
			{
				c_arr[i + 1] = arr[i] + count;
			}
			count += 10;
	
		printf("\nClient %d sending data along with reply port. \n", c_arr[0]);
		
		for(i = 1; i < 11; i++)
			printf("%d \t", c_arr[i]);
		printf("\n");
		send(80, c_arr);
		
		sleep(1);
		recv(c_arr[0], recv_arr);		
		printf("\nClient %d received data from port %d: \n", c_arr[0], c_arr[0]);
		
		for(i = 1; i < 11; i++)
			printf("%d\t", recv_arr[i]);
		printf("\n\n\n");
		
		sleep(1);
			
	}
}
/*
void client1(void)
{	
		
while(1){	
	
			
		int recv_arr[11], c_arr[11], i;
		client_id++;
		c_arr[0] = (client_id)%2;
		for(i = 0; i < 10; i++)
			{
				c_arr[i + 1] = arr[i] + count;
			}
			count += 10;

		printf("\nClient %d sending data along with reply port. \n", c_arr[0]);
		
		for(i = 1; i < 11; i++)
			printf("%d \t", c_arr[i]);
		printf("\n");
		send(0, c_arr);
	
		recv(c_arr[0], recv_arr);		
		printf("\nClient 2 received data from port %d: \n", c_arr[0]);
		
		for(i = 1; i < 11; i++)
			printf("%d\t", recv_arr[i]);
		printf("\n\n\n");
		
	
			
	}
}
*/

void server(void)
{
		int reply_port;
while(1){	
		
	
		int s_recv_arr[11], i;		
		recv(80, s_recv_arr);

		printf("\nReceived at server\n");
		for(i = 1; i < 11; i++)
			printf("%d\t", s_recv_arr[i]);
		sleep(1);
		reply_port = s_recv_arr[0];

	
		printf("\nSent to client %d from server.\n", s_recv_arr[0]);

		send(reply_port, s_recv_arr);

	
		
	}
}

void main()
{
	int i;
	
	lock = CreateSem(1);
	createPort();	
	
	start_thread(&client);
//	start_thread(&client1);
	start_thread(&client);
	start_thread(&server);

    	run();
    	while (1) sleep(1);




}
