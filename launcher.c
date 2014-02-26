#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <minix/igcreate.h>
#include <minix/iglookup.h>
#include <minix/igpublisher.h>
#include <minix/igsubscriber.h>
#include <minix/igpublish.h>
#include <minix/igsubscribe.h>
#include <minix/igadmin.h>
#define TRUE 1
#define FALSE 0

int main()
{
	int pid;pid_t p1;
	char choice;
	int result;
	int id = 0;
	int subchc;
	int i;
	int name;
	char term;
	char msg1[30];
	char igi[20];
	int len;

	char msg[] =
	"\n1.CREATE INTEREST GROUP\n2.JOIN INTEREST GROUP\n3.LOOK UP INTEREST GROUPS\n4.REGISTER AS A PUBLISHER TO AN INTEREST GROUP\n5.REGISTER AS A SUBSCRIBER TO AN INTEREST GROUP \n6.PUBLISH MESSAGE TO AN INTEREST GROUP\n7.SUBSCRIBE MESSAGES FROM AN INTEREST GROUP\n8.DELETE  AN INTEREST GROUP\n9.EXIT\n";
	
	while(1)
	{
		printf("\n******Welcome to Inter Process Communication******\n");
		printf("From Group 15 Deric Roshan Pinto, Dixitha Bharath Kumar\n"); 
		printf("%s",msg);
		printf("SELECT OUR OPTION :\n");
		scanf("%c",&choice);
		p1 = getpid();
		pid = (int) p1;
		switch(choice)
		{	
			
		case '1' :
			{	
				printf("ENTER THE ID OF THE IG YOU WANT TO CREATE  :\n");
			    if(scanf("%d%c", &name, &term) != 2 || term != '\n')
				printf("ENTER DATA PROPERLY:\n");
				else
				{
					result = igcreate(pid,TRUE,name);
					if(result == TRUE)
					printf("INTEREST GROUP  CREATED \n");
					else if(result == FALSE)
					{printf("INTEREST GROUP CANNOT BE CREATED\n");}
				}break;
			}
		case '2':
			{
				printf("ENTER THE ID OF THE IG YOU WANT TO JOIN\n");
				scanf("%d",&name);
				result = igcreate(pid,FALSE,name);
				if(result == TRUE)
					{printf("YOU HAVE BEEN JOINED TO INTEREST GROUP  \n");}
				else if(result == FALSE)
				{printf("YOU CANNOT BE JOINED TO THE INTEREST GROUP  \n");	}
				sleep(4);
			     break;
			}
		case '3':
			{
				 iglookup();
				 sleep(4);
			     break;;
			}
		case '4':
			{
			printf("ENTER THE ID OF THE IG YOU WANT TO REGISTER AS A PUBLISHER\n");
			scanf("%d",&name);
			result = igpublisher(pid,name);
			if(result == TRUE)
			{printf("SUCESS\n");}
			else
			{printf("NO SUCESS\n");}
			sleep(4);
			break;
			}
		case '5':
			{
			printf("ENTER THE ID OF THE IG YOU WANT TO REGISTER AS A PUBLISHER\n");
			scanf("%d",&name);
			result = igsubscriber(pid,name);
			if(result == TRUE)
			printf("SUCESS\n");
			else
			{printf("NO SUCESS\n");}
			sleep(4);
			break;
			}
		case '6':
			{
			printf("ENTER THE ID OF THE IG YOU WANT TO SEND MESSAGE\n");
			scanf("%d",&name);
			printf("ENTER THE MESSAGE YOU WANT TO SEND TO THE INTEREST GROUP\n");
			scanf("%s",msg1);
			if(igpublish(pid,name,msg1) == TRUE)
			printf("SUCESS\n");
			else
			{printf("NO SUCESS\n");}
			sleep(4);
			break;
			}
		case '7':
			{
			printf("ENTER THE ID OF THE IG YOU WANT TO RECEIVE MESSAGES FROM:\n");
			scanf("%d",&name);
			result = igsubscribe(pid,name,TRUE);
			if(result == TRUE)
			printf("SUCESS\n");
			else
			{printf("NO SUCESS\n");}
			sleep(4);
			break;
			}
		case '8':
			{
			printf("ENTER ID OF THE IG:\n");
			scanf("%d",&name);
			printf("ENTER PASSWORD:");
			scanf("%d",&i);
			result = igadmin(name,i);
			if(result == TRUE)
			printf("SUCESS\n");
			else
			{
					printf("NO SUCESS\n");
			}
			sleep(4);
			break;
			}
		case '9':
		{ 
			 return(1);
		}
		default:
			{
			 printf("wrong data\n");
			 break;
			}
	}
	
}
	printf("enter proper data:\n");
	return(1);
}
