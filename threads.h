/**
*@file "threads.h"
*@brief This is a header file used for running the thread program
*
*	This header file consists of the methods to start a thread
*	, to run the thread and a function to yield that is to swap the thread.
*
*@authors "Balaji Chandrasekaran"-1208948451
*	  "Kandhan Sekar" - 1209331327
*	  "Vimal Khanna Vadivelu" -1209203043 
*/

#include "q.h"				//includes the header file which contains the routine for Queue manipulation.

struct TCB_t *head=NULL;      			

/**
*@brief This function is used to start the thread.
*	
*	In this function we allocate memory for the stack
*	and call the init_TCB inorder to set the context
*	then the new node is added to the Queue.
*
*@param void function.
*@return void.
*/
void Start_Thread(void (*function)(void))
{
	void *stack = malloc(8192);
	struct TCB_t *tc = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	init_TCB(tc,function,stack,8192);
	AddQ(&head,tc);
}

/**
*@brief This funtion is for running the thread which is created/started.
*
*	In this funtion we run the thread and swap the thread which
*	is running with the one which is waiting next in the Queue.
*
*@param void.
*@return void.
*/

void Run()
{
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent,&(head->data));
}

/**
@brief This funtion is ussed for swapping the threads.
*
*	In this function we rotate the Queue and swap the
*	thread which is next in the Queue with the one which
*	is running.
*
*@param void.
*@return void.
*/
void Yield()
{
	RotateQ(&head);
	//ucontext_t parent;
	if(head == NULL)
		return;
	swapcontext(&(head->prev->data), &(head->data));
}
