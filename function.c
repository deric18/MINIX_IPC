#include<unistd.h>
#include<stdio.h>
#include<minix/callnr.h>
#include "pm.h"
#include<minix/endpoint.h>
#include<limits.h>
#include<minix/com.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<lib.h>
#include "function.h"
#include "param.h"
#include "mproc.h"

#define MAXSUB 5 
#define MAXPUB 1 
message mbuf;
extern IG * head;
extern int pass;
IG *node;
int id31;

int groupexists(int id)
{
	
	if(head == NULL)
	{
		return(FALSE);
	}
	else 
	{
		
		node = head;
		do
		{
			if(node->IGid==id)
			return(TRUE);
			node = node->next;
		}while(node != NULL);
		return(FALSE);
	} 
	return FALSE;
}


int insert(int id,int pid1)
{
	printf("INSERT\n");
	IG *new;
	if(head == NULL)
	{       
		head = (IG*)malloc(sizeof(IG));
		head->IGid = id;
		head->num_pub = 0;
		head->num_sub = 0;
		head->buffer_size = 0;
		head->num_pid = 0;
		head->pida[(head->num_pid)++] = pid1;
		head->next = NULL;
		head->flag = FALSE;
		return TRUE;
	}
	else if(head != NULL)
	{
		node = head;
		new = (IG*)malloc(sizeof(IG));
		new->num_pub = 0;
		new->IGid = id;
		new->num_sub = 0;
		new->buffer_size = 0;
		new->num_pid = 0;
		new->pida[(new->num_pid)++] = pid1;
		new->next = NULL;
		new->flag = FALSE;
		
		while(node->next!=NULL)
		{
			node = node->next;
				
		}
		node->next = new;
		return TRUE;
	}
	return FALSE;
}


int cilomppegr(int id, int pid1)
{
	printf("CILOMPPEGR\n");
	node = head;
	if(node == NULL)
	{
		printf("NO INTEREST GROUPS PRESENT \n");
		return FALSE;
 	}
	else if(node != NULL)
 	{	while( node!= NULL)
		{
 			if(node->IGid== id)
 			{
   				if(node->num_pid == MAX_PID)
   				{
			        printf("LIMIT REACHED NO MORE PROCESS\n");
    				return FALSE;
   				}
   				else
   				{	
			    	printf("SLOT AVAILABLE\n");
    				node->pida[++(node->num_pid)] = pid1;
			        return TRUE;
   				}
  			}
  			node=node->next;
		}
 	}
 return FALSE;
} 
int cpaig(int id,int pid1)
{
	printf("CPAIG\n");
	int i;
	node = head;
	while(node!= NULL)
	{
		if(node->IGid==id)
		{
			for(i=0;i<=(node->num_pid);i++)
			{
				if(pid1 == node->pida[i])
				{	
					printf("PROCESS ALREADY REGISTERED IN THE GROUP AS VALID PROCESS \n");
					return(TRUE);
				}
			}
			
		}
		node = node->next;
	}
	return(FALSE);
}

int do_IGcreate()
{
	printf("IGCREATE\n");
	IG *node = head;
	int iret;
	int i;
 	int icorj = m_in.corj;
	int pid2 = m_in.pidc;
    int id2 = m_in.length1;
	id31 = m_in.length1;
	
	
	if(icorj == TRUE)		/* creating the group */
	{
			printf("version 4:icorj:%d pid:%d id:%d\n",icorj,pid2,id2);
			if(groupexists(id2) == FALSE)
			{
				if(insert(id2,pid2) == TRUE) 
				{
					printf("GROUP SUCCEFUULLY CREATED \n");
					return TRUE;
				}
				printf("GROUP CANNOT BE CREATED :\n");
				return FALSE;
			}
			printf("GROUP WITH THIS NAME ALREADY EXISTS \n");
			return FALSE;
		
	}
	else if(icorj == FALSE) /* JOINING THE GROUP */
	{
		iret  = FALSE;
		if(groupexists(id2) == TRUE)
		{
			printf("GROUP EXISTS... ATTEMPTING TO JOIN \n");
			iret = TRUE;
		}
		else
		{ 
			printf("GROUP DOES NOT EXIST .. CHECK \n");
			return FALSE;
		}
		if(iret == TRUE)    /*GROUP EXISTS JOIN GROUP */
		{
			node = head;
			while(node!= NULL)	/*CHECKING PROCESS ALREADY REGISTERED IN THE GROUP */
			{
				if(node->IGid==id2)
				{
					for(i=0;i<(node->num_pid);i++)
					{
						if(pid2 == node->pida[i])
						{	
							printf("PROCESS ALREADY REGISTERED , CANNOT REGISTER AGAIN\n");
							return(FALSE);
						}
						if(node->num_pid == MAX_PID)
						{
							printf("NUMBER OF MEMBERS FOR THIS GROUP HAS REACHED LIMIT\n");
							return FALSE;
						}
					}
					break;
				}
				node = node->next;
			}
					/*NO CONSTRAINTS FOUND REGISTERING...*/
				printf("SLOT AVAILABLE\n");
    			node->pida[++(node->num_pid)] = pid2; 	
				printf("PROCESS JOINED THE GROUP\n");
				return TRUE;
		 }
	}
	return FALSE;
}
void do_IGlookup(void) 
{
	int i;
	node = head;
	if(node == NULL)
	{
		printf("THERE ARE NO INTEREST GROUPS TO DISPLAY\n");

	}
	else
	{
		printf("---ID-----TOTAL MEMBERS----NUMBER OF PUBLISHERS----- NUMBER OF SUBSCRIBERS-\n");
		while(node != NULL)
		{
			printf("   %d----------%d------------------%d-------------------------%d \n",node->IGid,node->num_pid,node->num_pub,node->num_sub);
			node = node->next;
		}
		node = head;
		while(node !=NULL)
		{
			if(node->IGid == id31)
			{
				printf("MEMBERS OF IG %d :",id31);
				for(i = 0;i<node->num_pid;i++)
				{
					printf("    %d",node->pida[i]);
				}
			}
			node = node->next;

		}
	}
}

int do_IGpublisher()
{
	node = head;
    int pid3 = m_in.pidper;
	int id2  = m_in.id1;
	id31 = m_in.id1;
	
	if(groupexists(id2) == FALSE)
    {
		printf("Group does not exist... check your spelling\n");
		return FALSE;
	}

	if(cpaig(id2,pid3) == TRUE)
	{
		printf("PROCESS ALREADY MEMBER. REGISTERING AS A PUBLISHER\n");
		node = head;
		while(node!=NULL)
		{	if(node->IGid==id2)
			break;
			node = node->next;
		}
		if(node != NULL)
		{
			if(node->num_pub == MAXPUB) 	
		    {
				printf("MAX PUB REACHED\n");
				return FALSE;
			} 
			else
			{
				node->pub_pid[(node->num_pub)++] = pid3;
				printf("SUUCESSFULY REGISTERED\n");
				return TRUE;
			}
		}
	}
	else
	{
		printf("PROCESS NOT A MEMBER  REGISTERING NOW... \n");
		node = head;
		while(node!=NULL)
		{	if(node->IGid==id2)
			break;
			node = node->next;
		}
		if(node != NULL)
		{
			if(node->num_pid == MAX_PID)
			{
				printf("LIMIT OF MAX MEMBERS REACHED \n");
				return FALSE;
			}
			if(node->num_pub == MAX_PUB) 	
		    {
				printf("MAX PUB REACHED\n");
				return FALSE;
			} 
			else
			{
				node->pida[(node->num_pid)++] = pid3;
				node->pub_pid[(node->num_pub)++] = pid3;
				printf("SUUCESSFULY REGISTERED\n");
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

int do_IGsubscriber()
{

    node = head; 
	int pid2 = m_in.pidser;
	int id2 = m_in.id1;
	id31 = m_in.id1;
	int i;
	if(groupexists(id2) == FALSE)
 	{
		printf("ERROR: NO SUCH GROUP EXISTS  %d",id2);
		return FALSE;
	}
	if(cpaig(id2,pid2) == TRUE)
	{
		printf("PROCES  ALREADY A MEMBER OF THE GROUP\nREGISTERING AS A SUBSCRIBER\n");
		node = head;
		while(node!=NULL)
		{
			if(node->IGid==id2)
			break;
			node = node->next;
		}
		if(node != NULL)
		{
			for(i = 0;i< node->num_sub ;i++)
			{
				if(node->sub_pid[0][i] == pid2)
				{
					printf("PROCESS ALREADY REGISTERED AS SUBSCRIBER IN %d SLOT CANNOT BE REGISTERED AGAIN\n",i);
					return FALSE;
				}
			}
			if(node->num_sub == MAX_SUB)
			{	
				printf("MAXIMUM SUBSCRIBERS REACHED \n");
				return FALSE;
			}
			else
			{
				node->sub_pid[0][node->num_sub] = pid2;
				node->sub_pid[1][node->num_sub] = 0;
				node->num_sub++;
				return TRUE;
			}
		}
			
	}
	else
	{
		printf("PROCESS NOT A MEMBER OF IG REGISTERING NOW... \n");
		node = head;
		while(node!=NULL)
		{	if(node->IGid==id2)
			break;
			node = node->next;
		}
		if(node != NULL)
		{
			printf("IG FOUND\n");
			if(node->num_pid == MAX_PID)
			{
				printf("LIMIT OF MAX MEMBERS REACHED \n");
				return FALSE;
			}
			if(node->num_sub == MAX_SUB) 	
		    {
				printf("MAX SUB REACHED\n");
				return FALSE;
			} 
			else
			{
				node->pida[node->num_pid++] = pid2;
				node->sub_pid[0][(node->num_sub)] = pid2;
				node->num_sub++;
				printf("SUCESSFULY REGISTERED\n");
				return TRUE;
			}
		}
		return FALSE;
	}
	return FALSE;
	
}
int do_IGpublish() 
{
	IG *node;
	int pid2 = m_in.pidp;
	int id2  = m_in.len123;
	id31 = m_in.len123;
	int b = FALSE ;
	int i;
    node =  head; 
      while(node!=NULL)
      {
		if(node->IGid==id2)
		{
			printf("SEARCHING FOR IG REQUESTED\n");
			for(i=0; i<=(node->num_pub); i++)
			{
				if(node->pub_pid[i] == pid2)
				b = TRUE;
			}
			if(b==FALSE)
			{
				printf("YOU ARE NOT REGISTERED AS A PUBLISHER FOR THIS IG\n");
				return(FALSE);
			}
			if(node->buffer_size == BUF_SIZE)
			{
				printf("BUFFER MEMORY FULL\n");
				return(FALSE);
			}	
			if(node->flag == TRUE)
			{	
				printf("ERROR:SEND BLOCKED GROUP BUSY.. TRY AGAIN LATER");
				return(FALSE);
			}
			else
			{
				 node->flag = TRUE;
				 node->ptr[node->buffer_size]=(char*)malloc(sizeof(char)*30);
				 memcpy(mbuf.m3_ca1,m_in.m3_ca1,20);
				 memcpy(node->ptr[node->buffer_size],mbuf.m3_ca1,20);
				 printf("AM INSIDE PUBLISH NOW \n");
				 printf("RECEIVED MESSAGE: mbuf: %s \n",mbuf.m3_ca1);
				 printf("STORED MESSAGE: %s \n",node->ptr[node->buffer_size]);
				 node->buffer_size++;
				 node->flag = FALSE;
				 printf("MESSAGE RECEIVED SUCCESFULLY\n");
				 for(i=0; i<(node->num_sub); i++)
				 {
					node->sub_pid[1][i] = 0;
				 }
					return TRUE;
			}
		}
		node=node->next;
	}
	if(node==NULL)  
	{
		printf("THERE IS NO INTEREST GROUP LIKE THAT..\n");
		return(FALSE);
	}
	return FALSE;
}

int do_IGsubscribe()
{	
	int pid2 = m_in.pids;
	int stat = m_in.length1;
	int id2  = m_in.corj;
	int i;
	id31 = m_in.corj;
	int b = FALSE;
	if(stat == TRUE)
	{
      node =  head;
      while(node!=NULL)
      {
	    printf("SEARCHING FOR REQUESTED IG \n");
		if(node->IGid==id2)
		{
			printf("NODE FOUND .. VERFYING..\n");
			for(i=0; i<(node->num_sub); i++)
			{
				if(node->sub_pid[0][i] == pid2)
				{
					stat = i;
					b = TRUE;
					break;
				}
				
			}
			if(b == FALSE)
			{
				printf("YOU ARE NOT REGISTERED AS A SUBSCRIBER FOR THIS IG\n");
				return(FALSE);
			}
			if(node->buffer_size == 0)
			{
				printf("BUFFER MEMORY EMPTY\nNO MESSAGES TO SHOW YOU\n");
				return(FALSE);
			}
			if(node->sub_pid[1][stat]==0)
			{
					printf("IG FOUND: RETRIEVING MSG FROM MEMORY\n");
					printf("MESSAGES FOR IG %d :\n",id2);
					printf("MSG NUM-----MESSAGE-\n");
					for(i = 0;i<node->buffer_size;i++)
					printf("  [%d]   :    %s \n",i,node->ptr[i]);
					for(i=0;i<node->num_sub;i++)
					{
						if(node->sub_pid[0][i] == pid2)
						node->sub_pid[1][i] = 1;
					}
			
				printf("CHECKING ALL SUBSCRIBERS HAVE READ THE MESSAGE\n");
				for(i=0;i<node->num_sub;i++)
				{
					if(node->sub_pid[1][i]==0)
					{
					printf("MESSAGES NOT READ BY ALL SUBSCRIBERS YET\n");
					return (TRUE);
					}
				}
				for(i = 0;i<node->buffer_size;i++)
				free(node->ptr[i]);
				node->buffer_size = 0;
				for(i=0;i<node->num_sub;i++)
				{
					node->sub_pid[1][i] = 0;
				}
				printf("messages deleted succesfully\n");
				return TRUE;
			}
			else if(node->sub_pid[1][stat]==1)
			{
				printf("NO NEW MESSAGES TO SHOW YOU\n");
				return FALSE;
			}
			return FALSE;

		}
		node=node->next;
		}
		if(node==NULL)  
		{
			printf("THERE IS NO INTEREST GROUP LIKE THAT..\n");
			return(FALSE);
		}
		return FALSE;
	}
	return FALSE;
}
int do_IGadmin()
{
	IG *temp;
	int igid = m_in.pidc;
	int pass1 = m_in.corj;
	int i = 0;
	int j = 0;
	if(pass1 == pass)
	{
		if(groupexists(igid) == TRUE)
		{
				node  = head;
				while(node!=NULL)
				{
					if(node->IGid == igid)
					{
						i++;
						break;
					}
					j++;
					node = node->next;
				}
				if(i > j)
				{
					printf("DELETING THE FIRST NODE \n");
					node = head;
					while(node!=NULL)
					{
						head = node->next;
						free(node);
						return TRUE;
					}
					
				}
				else if(i<=j)
				{
					node  = head;
					while(node!=NULL)
					{
						temp = node->next;
						if(temp->IGid == igid)
						{
							node->next = temp->next;
							printf("GROUP DELETED SUCCESFULLY\n");
							free(temp);
							return TRUE;
						}
						node = node->next;
					}
					printf("NO SUCH GROUP EXISTS\n");
					return FALSE;
				}
				
		}
		else
		{
			printf("NO SUCH GROUP\n");
			return FALSE;
		}
	}
	else
	{
		printf("\nAUTHORIZATION FAILED\n");
		return FALSE;
	}
	return FALSE;
}
	

