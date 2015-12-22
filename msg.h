/**
*@file "msgs.h".
*@brief synchronization
* 	
*	This file contains the synchronization routine between 		
*	the ports.	
* 
*@authors "Balaji Chandrasekaran"-1208948451
*	  "Kandhan Sekar" - 1209331327
*	  "Vimal Khanna Vadivelu" -1209203043 		
*/

#include<stdio.h>
#include"sem.h"


const int N=100;//number of ports
int i=0,j=0,k=0;
int c=0;


typedef struct mess{
int mess_value[10][10];//Dimension 1 - number of messages , Dimension 2 - Each message can have 10 integers
Semaphore_t *sem_send;
Semaphore_t *sem_recv;
Semaphore_t *mutex;
int in;
int out;
}message_struct;



//each ports will have a producer and consumer semaphore and a mutex - strategy 2
message_struct *ports[100];


// initializing the message structure

void init_mess()
{
	
	for(i=0;i<N;i++)
		{

			ports[i]=(message_struct *)malloc(sizeof(message_struct));
			ports[i]->sem_send = CreateSem(0);
			ports[i]->sem_recv = CreateSem(10);
			ports[i]->mutex = CreateSem(1);
			ports[i]->in=0;
			ports[i]->out=0;

			for(j=0;j<10;j++)
				{
					for(k=0;k<10;k++)
						{
							ports[i]->mess_value[j][k]=0;//init message values to 0

						}
				}
		}

}


//Send routine

void send(int ports_s,int message[])
{

P(ports[ports_s]->sem_recv);
P(ports[ports_s]->mutex);

//printf("\n inside send lock ");

for(i=0;i<10;i++)
	{
		ports[ports_s]->mess_value[ports[ports_s]->in][i]=message[i];
	}
ports[ports_s]->in=(ports[ports_s]->in+1)%10;

V(ports[ports_s]->mutex);
V(ports[ports_s]->sem_send);

}



//Receive routine

void receive(int ports_s,int message[])
{
P(ports[ports_s]->sem_send);
P(ports[ports_s]->mutex);

//printf("\n inside recieve lock ");

for(i=0;i<10;i++)
	{
		message[i]=ports[ports_s]->mess_value[ports[ports_s]->out][i];
	}

ports[ports_s]->out=(ports[ports_s]->out+1)%10;

V(ports[ports_s]->mutex);
V(ports[ports_s]->sem_recv);

}
