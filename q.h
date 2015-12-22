/**
*@file "Q.h".
*@brief intializes, creates , deletes, rotates the queue.
* 			
*		
*	This file contains the functions which are used to intialize
*	the circular doubly linked list(Queue), Add a new element to the
*	Queue, Roatate the queue if necessary and a funtion to return a 
*	pointer to the node that is being deleted.
* 
*@authors "Balaji Chandrasekaran"-1208948451
*	  "Kandhan Sekar" - 1209331327
*	  "Vimal Khanna Vadivelu" -1209203043 		
*/

#include<stdlib.h>
#include "tcb.h"		// tcb.h is the header file created by us.


//prototypes of the funtion.

void InitQ(struct TCB_t **head);
void RotateQ(struct TCB_t **head);
void AddQ(struct TCB_t **head, struct TCB_t *item);
struct TCB_t* DelQ(struct TCB_t **head);

/**
*@brief Function will intialize the Queue.
*	
*	This funtion is used inorder to intialize.
*	
*@param head head is a double pointer to the head of the Queue.
*@return void .
*/
void InitQ(struct TCB_t **head)
{
     	
	(*head)->next = (*head);
	(*head)->prev = (*head);
}

/**
*@brief Funtion to add node to the Queue.
*
*
*	This funtionc adds the node item to the tail of the 
*	Queue, checks if the node to be added is the first
* 	node or not and adds the node accordingly.
*
*@param head Double pointer to the head node of Queue.
*@param item Pointer to the node that should be added.
*@return void.
*/

/*
void AddQ(struct TCB_t **head, struct TCB_t *item)
{
	struct TCB_t *temp;
	temp=(struct TCB_t*)malloc(sizeof(struct TCB_t));
	temp->data = item->data;
	if(*head==NULL)					// checks if this is the first node.
	{
		temp->next = temp;
		temp->prev = temp;
		(*head)=temp;				// makes the new node as the head node.
	}
	else
	{
		temp->next = (*head);
		temp->prev = (*head)->prev;
		(*head)->prev->next=temp;
	}
	(*head)->prev=temp;
	//printf("\n end of add");
}
*/

void AddQ(struct TCB_t **head,struct TCB_t *item)
{
    if(*head==NULL)//to add the first node when the queue is empty
    {
        *head = item;
        (*head)->data=(item)->data;
        InitQ(head);//calling initQ method
    }
    
    else//add node to the existing queue(queue not empty)
    {
        struct TCB_t *temp=(*head);

        (*head)->prev->next=(item);
        (item)->prev=(*head)->prev;
        (*head)->prev=(item);
        (item)->next=*head;
    }
    
}

/**
*@brief Function to delete a node from the Queue.
*
*
*	This funtion deletes the node from the head of the Queue
*	and the returns a pointer to the deleted node, it also
*	makes the next node to the head as the new head node.
*
*@param head Double pointer to the head of the Queue.
*return The pointer to the node to be deleted.
*/

struct TCB_t* DelQ(struct TCB_t **head)
{
	if((*head)==NULL)
	{
		printf("no elements in queue\n");
		return NULL;
	}
	struct TCB_t *temp;				// pointer to node to be returned.
	temp=(struct TCB_t*)malloc(sizeof(struct TCB_t));
	temp->data =(*head)->data;
	temp->next = (*head)->next;
	temp->prev = (*head)->prev;

	if((*head)->next == (*head))			// if only head node is present.
	{
		free(*head);
		(*head)=NULL;
	}
	else
	{
		TCB_t *ptmp = *head;
		(*head)->prev->next=(*head)->next;
		(*head)->next->prev=(*head)->prev;
		(*head)=(*head)->next;
		free(ptmp);
	}

	return temp;
}


/**
*@brief Funtion to roatate the Queue.
*	
*
*	This function is used inorder to roatate the Queue
* 	it makes the head as the end of the queue and makes 
*	the node next to the head as the new head node.
*
*@param	head Double pointer to the head of the Queue.
*@return void.
*/
void RotateQ(struct TCB_t **head)
{

	if( (*head)==NULL)
	{
		printf("cannot rotate the queue\n");
	}
	else
	{
		(*head)=(*head)->next;
	}
}
