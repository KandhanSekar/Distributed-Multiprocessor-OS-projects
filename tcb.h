
/**
*@file "tcb.h"
*@brief This file is a header which contains method for stack manipulation.
*
*	In the file we define the structure of the node in the Queue
*	, we also create a method which gets the context of the calling
*	thread ,sets the stack pointer and size ,later modifies the context 
*
*@authors "Balaji Chandrasekaran"-1208948451
*	  "Kandhan Sekar" - 1209331327
*	  "Vimal Khanna Vadivelu" -1209203043 
*/

#include<ucontext.h>
#include<stdio.h>
#include<string.h>


struct TCB_t				// Stucture definition of node of Queue.
{
ucontext_t data;
struct TCB_t *next;
struct TCB_t *prev;
};

typedef struct TCB_t TCB_t;

/**
@brief init_TCB function used for context and setting up of pointer to stack, stack size.
*
*	This function is used for making the context which is got from the node,
*	it also creates the stack pointer and sets the size of the stack.
*
*@param TCB_t It is of the struct node type of the Queue.
*@param void funtion.
*@param  StackP Pointer to the stack.
*@param Stack_size Size of the stack
*@return void.
*/
void init_TCB(struct TCB_t *tcb,void *function,void *stackP,int stack_size)
{
	memset(tcb,'\0',sizeof(struct TCB_t));		
	getcontext(&tcb->data);				// gets the context of the calling thread.
	tcb->data.uc_stack.ss_sp=stackP;		// points the stack pointer to the current context.
	tcb->data.uc_stack.ss_size=(size_t) stack_size;	// asigns the size of the stack.
	makecontext(&tcb->data,function,0);		// modifies the context.
}
