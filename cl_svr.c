#include<string.h>
#include<stdlib.h>
#include<ucontext.h>
#include "msgs.h"
#define str_size 	100
#define server_port	 99
#define cl_1		 1
#define cl_2 		 2
#define cl_3 		 3
#define packet_size	36
#define string_size 100

char table[10][100] = {"Blank1", "Blank2", "Blank3", "Blank4", "Blank5", "Blank6", "Blank7", "Blank8", "Blank9", "Blank10"};
char randomstr[10][100] = {"Google", "Amazon", "Blackberry", "Microsoft", "Apple", "Qualcomm", "eBay", "IBM", "Intel", "Yahoo"};

void ADD(int index, char *str, int recv_port)
{
	printf("\nAdding %s to the table at index: %d, received from client %d.\n", str, index, recv_port);
	memset(&table[index], 0, str_size);
	memcpy(&table[index], str, strlen(str) + 1);
}

void Modify(int index, char *str, int recv_port)
{
	printf("\nClient %d modified table entry at %d to %s\n", recv_port, index, str);
	memset(&table[index], 0, str_size);
	memcpy(&table[index], str, strlen(str) + 1);
}

void Delete(int index, int recv_port)
{
	printf("\nClient %d deleted table entry at index: %d\n", recv_port, index);
	memset(&table[index], 0, str_size);
}

int Retrieve(char *tablestr) 
{
	int i = 0;
	char* temp1 = (char *) malloc(string_size);
	temp1 = table[0];
	strcpy(tablestr,temp1);
	const char *space = (char*)" ";
	for(i =1;i<10;i++)
	{
		char* temp2 = (char *) malloc(string_size);
		temp2 = table[i];
		if(strlen(temp2)!=0)
		{
			strcat(tablestr,space);
			strcat(tablestr,temp2);
		}
			
	}
	
	return strlen(tablestr);
}

void Server()
{
	int msg[10], tableArr[10] ;
	int action, recv_port, index, len = 0, size;
	char *tablestr = (char *)malloc(sizeof(char) * 10 * str_size);	
	printf("\nServer started!!\n");
	while(1)
	{	
		int i =0, flag;
		recv(server_port, msg);
		recv_port = msg[0];
		action = msg[1];
		index = msg[2];

		switch(action)
		{
			case 0: ADD(index, (char *)&msg[3], recv_port);					//ADD
				send(recv_port, msg);
				break;
			case 1: Modify(index, (char *)&msg[3], recv_port);				//Modify
				send(recv_port, msg);
				break;
			case 2: Delete(index, recv_port);						//Delete
				send(recv_port, msg);
				break;
			case 3: flag = 1;								//Retrieve
				Retrieve(tablestr);
				len = strlen(tablestr);

				while(flag) {
					size = (len>packet_size)?packet_size:len;
					memset(tableArr,0,sizeof(int)*10);		
					memcpy(&tableArr[1], tablestr+i, size);
					i+=size;
					len -= size;
					if(len<=0){
				  		 flag = 0;	
						 tableArr[0] = 0;
					}
					else {
						tableArr[0] = 1;
					}

					send(recv_port, tableArr);
				}
	   			break;
			 default :
           			printf("Error\n");
           			break;
		}
	}
}

void Client1()
{
	int msg[10];
	int client_port = cl_1;
	int randNum = 0;
	printf("\nClient 1 started!!\n");
	for(;;)
	{
		randNum = rand() % 10;
		msg[0] = client_port;
		msg[1] = 1;			//action = Modify
		msg[2] = randNum;
		memcpy(&msg[3],randomstr[randNum], strlen(randomstr[randNum]) + 1);
		send(server_port, msg);

		recv(client_port, msg);

		randNum = rand() % 10;
		msg[1] = 0;			//action = ADD
		msg[2] = randNum;
		memcpy(&msg[3],randomstr[randNum], strlen(randomstr[randNum]) + 1);
		send(server_port, msg);

		recv(client_port, msg);

		randNum = rand() % 10;
		msg[1] = 2;			//action = Delete
		msg[2] = randNum;
		send(server_port, msg);

		recv(client_port, msg);
	}
}

void Client2()
{
	int msg[10];
	int client_port = cl_2;
	int randNum = 0;
	printf("\nClient 2 started!!\n");
	for(;;)
	{
		randNum = rand() % 10;
		msg[0] = client_port;
		msg[1] = 1;			//action = Modify
		msg[2] = randNum;
		memcpy(&msg[3],randomstr[randNum], strlen(randomstr[randNum]) + 1);
		send(server_port, msg);

		recv(client_port, msg);

		randNum = rand() % 10;
		msg[1] = 0;			//action = ADD
		msg[2] = randNum;
		memcpy(&msg[3],randomstr[randNum], strlen(randomstr[randNum]) + 1);
		send(server_port, msg);

		recv(client_port, msg);

		randNum = rand() % 10;
		msg[1] = 2;			//action = Delete
		msg[2] = randNum;
		send(server_port, msg);

		recv(client_port, msg);
	}
}

void Client3()
{	
	
	int msg[10], i;
	int client_port = cl_3;
	printf("Client 3 started.\n");
	for(;;)
	{
		int count = 0;		

		msg[0] = client_port;
		msg[1] = 3;			//action = Retrieve
		send(server_port, msg);		
		int flag = 1;
		printf("\n########################## | Table received by client 3 | ########################\n");
		while(flag) {	

			recv(client_port, msg);	
			if(msg[0] == 0)
			{	
				flag = 0;
			}
			char *msg_str = (char*)&msg[1];
			
			for(i = 0;i<strlen(msg_str);i++)
			{
				if(msg_str[i] == ' ')
					printf("\n");
				else
					printf("%c",msg_str[i]);
			}
					
		}	
		printf("\n##################################################################################\n");	
		sleep(2);	
	}
		
	
}

void main()
{
	createPort();

	start_thread(&Server);
	start_thread(&Client3);
	start_thread(&Client1);
	start_thread(&Client2);
	
	run();

	while(1) sleep(1);
}



