/**
*@file "cl-srv.c".
*@brief synchronization
* 	
*	This file contains the communication between three Client and 
*	One Server , in which one client is responsible for randomly printing
*	and other two clients are responsible for adding,deleting and modifying
* 	string in the server. Server contains entries of 10 strings.		
*		
* 
*@authors "Balaji Chandrasekaran"-1208948451
*	  "Kandhan Sekar" - 1209331327
*	  "Vimal Khanna Vadivelu" -1209203043 		
*/
#include<stdio.h>
#include "msg.h"
#include<stdlib.h>
#include<math.h>

int cport=0;

void client()
{
	int num[10];//integer message array - extra i guess 
	int clnt=0,sp=0,i=0,j=0,k=0;
	int pos=-1;
	char imessage1[2][10]={"Abscond","rivalry"};
	char imessage2[2][10]={"Brother","Systems"};
	char imessage3[10]={"Recieve"};
	int random_index=0;
	int int_msg1[10];
	int int_msg2[10];
	int int_msg3[10];
	if(cport<99){
			clnt=++cport;
					while(1){
						if(clnt==1){
							    random_index=random()%2;
							    imessage1[random_index][9]=clnt; //10th position is allotted for client port
							    imessage1[random_index][8]=rand()%10; // 9th position is allotted in case of case 2
							    imessage1[random_index][7]=rand()%3;//specifies a random operation
							    char oper1[30]="Add to table";
							    char oper2[30]="Replace with L";
  							    char oper3[30]="Modify each char(+4)";
							    printf("\n At Client: \n \tMessage:- \n\t\t  To server %d \n\t\tFrom Client %d is: \t",0,clnt);
 							    for(j=0;j<7;j++)
  								{
									int_msg1[j]=(int)imessage1[random_index][j];
								}
							    for(j=7;j<10;j++)
								{
									int_msg1[j]=imessage1[random_index][j];
								}
							    for(j=0;j<7;j++)
								{
									printf("%c ",imessage1[random_index][j]);
								}
								printf("\n THE operation is ");

							    switch(imessage1[random_index][7])
								{
									case 0:printf("%s",oper1);
									break;

									case 1:printf("%s",oper2);	
									break;

									case 2:printf("%s",oper3);
									break;
								}


								sleep(1);
								printf("\n");	
								send(0,int_msg1);
							}
						else if(clnt==2){
								char oper1[30]="Add to table";
	      							char oper2[30]="Replace with L";
								char oper3[30]="Modify each char(+4)";
								random_index=random()%2;
								imessage2[random_index][9]=clnt;//10th pos is allotted for client port
								imessage2[random_index][8]=rand()%10;
								imessage2[random_index][7]=rand()%3;
								printf("\n \tMessage:- \n\t\t  To server %d \n\t\tFrom Client %d is: \t",0,clnt);
								for(j=0;j<7;j++)
								{	
									int_msg2[j]=(int)imessage2[random_index][j];
								}
								for(j=7;j<10;j++)
								{
									int_msg2[j]=imessage2[random_index][j];
								}
								for(j=0;j<7;j++)
								{
									printf("%c ",imessage2[random_index][j]);
								}
								printf("\n THE operation is ");

								switch(imessage1[random_index][7])
								{
									case 0:printf("%s",oper1);
									break;

									case 1:printf("%s",oper2);
									break;

									case 2:printf("%s",oper3);
									break;
								}


								sleep(1);
								printf("\n");
								send(0,int_msg2);
							}
							
							int result[10][20];
							for(i=0;i<10;i++)
							{	
								for(j=0;j<20;j++)
								{
									result[i][j]=(int)'#';
								}
							}



						if(clnt==3){

								imessage3[9]=clnt;//10th pos is allotted for client port
								imessage3[8]=rand()%10;
								imessage3[7]=rand()%3;
								printf("\n ONLY ONE SEND REQUEST FROM THIS CLIENT:Message sent to server %d from Client %d is:\t",0,clnt);
								for(j=0;j<7;j++)
								{
									int_msg3[j]=(int)imessage3[j];
								}
								for(j=7;j<10;j++)
								{
									int_msg3[j]=imessage3[j];
								}
								for(j=0;j<7;j++)
								{
									printf("%c ",imessage3[j]);
								}
								sleep(1);
								printf("\n");
								//Send only one request to server
								send(0,int_msg3);
								//Receive all entries from server table
								receive(clnt,result[0]);
								receive(clnt,result[1]);
								receive(clnt,result[2]);
								receive(clnt,result[3]);
								receive(clnt,result[4]);
								receive(clnt,result[5]);
								receive(clnt,result[6]);
								receive(clnt,result[7]);
								receive(clnt,result[8]);
								receive(clnt,result[9]);
								printf("\n ****** Client:Message (10 Strings) received from Server %d at Client %d ****** \n\t\t\t.# denotes the field is empty\n", sp,clnt);
								for(i=0;i<10;i++)
								{
									printf("\n");
									for(j=0;j<7;j++)
										{
											printf("%c ",result[i][j]);	
										}
								}
							}
							printf("\n");
							sleep(5);	
						}
			}
			else
			printf("\nNo more ports \n");
}



void server()
{
	int counter=0;
	char server_table[10][20];
	int server_table_t[10][20];

	int pos=0;
	int operation=0;
	int cp=0;
	int final_num[10];
	int i=0,j=0;

	for(i=0;i<10;i++)
	{
		for(j=0;j<20;j++)
		{
			server_table[i][j]='#';
		}
	}
	while(1)
	{
    		receive(0,final_num);
    		cp=final_num[9];
		printf("\n## Server:Message received at Server %d from Client %d \n",0,cp);
    		if(cp==3)
		{
			printf("\n'HERE IN %d'",cp);
			printf("\n@ Server:Sending response from Server %d to Client %d as 10 parts \n",0,cp);
			for(i=0;i<10;i++)
			{
				for(j=0;j<10;j++)
				{
				server_table_t[i][j]=(int)server_table[i][j];
				}
			}
			//Send response to clients
    		send(cp,server_table_t[0]);
    		send(cp,server_table_t[1]);
		send(cp,server_table_t[2]);
		send(cp,server_table_t[3]);
		send(cp,server_table_t[4]);
		send(cp,server_table_t[5]);
		send(cp,server_table_t[6]);
		send(cp,server_table_t[7]);
		send(cp,server_table_t[8]);
		send(cp,server_table_t[9]);
		}
		else
		{
			pos=final_num[8];
			operation=final_num[7];
			//Server Operations
			if(operation==0)
			{
				for(i=0;i<7;i++)
				{
					server_table[counter][i]=(char)final_num[i];
				}
				counter=(counter+1)%10;
			}
			else if(operation==1)
			{
				for(i=0;i<7;i++)	
				{
					server_table[pos][i]='L';
				}
			}
			else
			{
				for(i=0;i<7;i++)
				{
					server_table[pos][i]=(char)(final_num[i]+4);
				}
			}
	    	}
	}
}


int main()
{
printf("\n\t\t\t **************  Message passing with 1 Server port and 3 Client port  ************** \n");
printf("\n\t\t This program is a message passing with  1 Server port which contains 10 entries all of them being string and 3 Client port in which  first and second client port are responsible for add/delete or modify strings at random and client port 3 is responsible for printing \t \t \n");
init_mess();//initialize structure variables sem_send,sem_recv and mutex . Initialize message array to zeroes
//Starting 3 client and 1 server thread
Start_Thread(client);
Start_Thread(client);
Start_Thread(client);
Start_Thread(server);
Run();//call run

}
