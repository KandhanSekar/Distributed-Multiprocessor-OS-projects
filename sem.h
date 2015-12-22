/**
*@file sem.h
*@authors "Balaji Chandrasekaran"-1208948451
*	  "Kandhan Sekar" - 1209331327
*	  "Vimal Khanna Vadivelu" -1209203043 		
*/


#include<stdio.h>
#include<stdlib.h>
#include "threads.h"


typedef struct sem
{
int i;
struct TCB_t *h;
}Semaphore_t;

 
Semaphore_t* CreateSem(int InputValue)
{
Semaphore_t *S = (Semaphore_t*)malloc(sizeof(Semaphore_t));
S->i=InputValue;
S->h = NULL;
return S;
}

void P(Semaphore_t *sem) 	//P(semaphore) implementation
{
sem->i--;
struct TCB_t *temp;
temp=NULL;
if(sem->i<0)
{
	temp = DelQ(&head);
	if (temp) {
	//printf("\n inside p %d ", sem->i);
	AddQ(&(sem->h),temp);
	//printf("\n inside p after add");

	swapcontext(&(temp->data),&(head->data));
	//printf("\n inside p after swap ");
	//printf("\n end of p");
	}
}

}

void V(Semaphore_t *sem)	//V(semaphore) implementation
{
sem->i++;
struct TCB_t *temp;
if((sem->i)<=0)
{
temp=DelQ(&(sem->h));
if(temp)
{
AddQ(&head,temp);
}
}
Yield();
}
