#include <stdio.h>
#include <stdlib.h>
#include "TCB.h"

void InitQ(struct TCB_t **q)
{
	*q = NULL;
}

void AddQ(struct TCB_t **q, TCB_t *data_item)		//Adding an element in the queue.
{
	struct TCB_t *temp, *ptr = NULL;
	
	temp = malloc(sizeof(struct TCB_t));	
	temp = data_item;

	if(*q == NULL)				//Empty queue.
	{

		temp->next = temp;
		temp->prev = temp;
		*q = temp; 
	}
	else
	{

		ptr = (*q);
		while(ptr->next != (*q))		//Getting to the end of the queue.
		{
			ptr = ptr->next;
		}

		temp->prev = ptr;
		ptr->next = temp;
		temp->next = *q;
		(*q)->prev = temp;

	}
}

struct TCB_t *DelQ(struct TCB_t **q)			//Deleting an element from the queue head.
{
	struct TCB_t *temp, *ptr;
	temp = malloc(sizeof(struct TCB_t));
	
	temp = NULL;
	ptr = *q;
	
	if(*q == NULL)					//Empty queue.
	{
		printf("Ques is empty...Nothing to delete.");
		return NULL;
	}
	else if((*q)->next == *q)			//If queue has only one element.
	{
		temp = *q;
		free(*q);
		*q = NULL;
		return temp;
	}
	else
	{
		while(ptr->next != *q)
		{
			ptr = ptr->next;
		}
		temp = *q;
		*q = (*q)->next;
		ptr->next = *q;
		(*q)->prev = ptr;
	
		temp->next = NULL;
		temp->prev = NULL;
	}

	return temp;
}

void RotateQ(struct TCB_t **q)				//rotating the queue.
{
	struct TCB_t *temp;
	temp = malloc(sizeof(struct TCB_t));
	*q = (*q)->next;
	(*q)->prev = temp;
	temp->next = *q;
}
