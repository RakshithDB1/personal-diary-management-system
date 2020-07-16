#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

struct node
{
	char name[25];
	char time[6];
	char place[20];
	int count;
	char date[11];
	char note[650];
	struct node* rlink;
	struct node* llink;
};

typedef struct node* NODEPTR;

NODEPTR fnNotification(NODEPTR head);
void update(NODEPTR head);
NODEPTR fnSearchrecord_name(NODEPTR head,char N[25]);
void nodefree(NODEPTR temp);
void fnsetpassword();
void fnDisplay(NODEPTR head);
NODEPTR fnDeleterecord(NODEPTR head,char d[11],char t[6]);
NODEPTR fnAddrecord(NODEPTR head);
NODEPTR nodecreate();
bool checkpassword(char str1[20]);
void fnresetpassword();
NODEPTR restore(NODEPTR head);
NODEPTR fnEditrecord(NODEPTR head,char d[11],char t[6]);
NODEPTR fnViewrecord(NODEPTR head,char d[11],char t[6]);

/***************************************************************************
*Function			: 	main
*Input parameters	:	no parameters
*RETURNS			:	0 on success
***************************************************************************/

int main(int argc, char *argv[])
 {
 	int ichoice1,ichoice2,n;
 	FILE *fp1;
 	char str1[20],d[11],t[6],iName[25];
 	NODEPTR head;
 	head=nodecreate();
 	head->rlink=head->llink=head;
 	
 	for(;;)
 	{
 		printf("\n*************PERSONAL DIARY**********************\n");
 		printf("\n********************MAIN MENU**************************\n");
 		printf("1.NEW USER\n2.LOGIN\n3.EXIT\n");
 		printf("\nEnter your choice\n");
 		scanf("%d",&ichoice1);
 		if(ichoice1==3)
 		{
 			exit(0);
		}
		if(ichoice1==2)
		{
			printf("\nEnter the password(20 characters max and no space):");
			scanf("%s",str1);
			if(checkpassword(str1)!=true)
			{
				printf("\nWrong password\n");
				continue;
			}
			head=restore(head);
			head=fnNotification(head);
		}
		if(ichoice1==1)
		{
			fnsetpassword();
			head->count=0;
		}
		if(ichoice1!=2&&ichoice1!=1)
		{
			printf("\nInvalid choice\n");
			continue;
		}
		for(;;)
		{
			printf("\n****************PERSONAL DIARY*************************\n");
			printf("\n*********************MENU************************\n");
			printf("1.ADD RECORD\n2.DELETE RECORD\n3.DISPLAY ALL RECORDS\n4.RESET PASSWORD\n5.EDIT RECORD\n6.View Record");
			printf("\n7.Search reocrd by name\n8.back to main menu\n9.exit\n");
			printf("\nEnter your choice\n");
			scanf("%d",&ichoice2);
			switch(ichoice2)
			{
				case 1:head=fnAddrecord(head);
					   break;
				case 2:printf("\nEnter the date:");
					   scanf("%s",d);
					   printf("\nEnter the time:");
					   scanf("%s",t);
					   head=fnDeleterecord(head,d,t);
					   break;
				case 3:fnDisplay(head);
					   break;
				case 4:fnresetpassword();
					   break;
				case 5:
					   printf("\nEnter the date:");
					   scanf("%s",d);
					   printf("\nEnter the time:");
					   scanf("%s",t);
					   head=fnEditrecord(head,d,t);
					   break;
					   
				case 6:printf("\nEnter the date:");
					   scanf("%s",d);
					   printf("\nEnter the time:");
					   scanf("%s",t);
					   head = fnViewrecord(head,d,t);
					   break;
				case 7:printf("\nEnter the Name:");
					   scanf("%s",iName);
					   head=fnSearchrecord_name(head,iName);
					   break;
					   
				case 8:break;
					   
				case 9:fp1=fopen("number.dat","w");
					   fprintf(fp1,"%d",head->count);
					   fclose(fp1);
					   update(head);
					   exit(0);
				default:printf("\nInvalid choice\n");
			}
			if(ichoice2==8)
			{	fp1=fopen("number.dat","w");
				fprintf(fp1,"%d",head->count);
				fclose(fp1);
				update(head);
				break;
			}
			
		}
 		
	 }
 	
	return 0;
}

/***************************************************************************
*Function			: restore
*Description		: Function to restore the data from the file 
*Input parameters	: Pointer which pointes to the header node
*	
*RETURNS			:Pointer which pointes to the header node
*	
***************************************************************************/

NODEPTR restore(NODEPTR head)
{
	NODEPTR first,second;
	FILE *fp,*fp1;
	int n=0,t;
	fp1=fopen("number.dat","r");
	fscanf(fp1,"%d",&t);
	fclose(fp1);
	head->count=t;
	first=nodecreate();
	first->llink=first->rlink=first;
	head->rlink=first;
	first->llink=head;
	head->llink=first;
	first->rlink=head;
	fp=fopen("a.dat","r");
	if(fp==NULL)
	{
	    printf("\nfile does not exist\n");
	    return head;
	}
		while(head->count!=n)
		{
			fscanf(fp,"\n%s\n%s\n%s\n%s\n",first->date,first->time,first->place,first->name);
			fgets(first->note,650,fp);
			n++;
			if(n!=head->count)
			{
				second=nodecreate();
				second->llink=second->rlink=NULL;
				first->rlink=second;
      			second->rlink=head;
     			head->llink=second;
      			second->llink=first;
				first=second;
			}
			
		}
		fclose(fp);
		return head;

}

/***************************************************************************
*Function			: update
*Description		: Function to update the data in the file
*Input parameters	:Pointer which pointes to the header node
*	
*RETURNS			:no value
*	
***************************************************************************/

void update(NODEPTR head)
{
	FILE *fp;
	NODEPTR first;
	int n=0;
	first=head->rlink;
	fp=fopen("a.dat","w");
	if(fp==NULL)
	{
		printf("File not found\n");
		return;
	}
	else
	{
		while(head->count!=n)
		{
			fprintf(fp,"\n%s\n%s\n%s\n%s\n",first->date,first->time,first->place,first->name);
			fputs(first->note,fp);
			n++;
			first=first->rlink;
			
		}
	}
	fclose(fp);
	return;
}

/***************************************************************************
*Function			: nodecreate
*Description		: Function to create new node
*Input parameters	:no Value
*	
*RETURNS			:Pointer which pointes to the newly created  node
*	
***************************************************************************/

NODEPTR nodecreate()
{
	NODEPTR newborn;
	newborn=(NODEPTR)malloc(sizeof(struct node));
	if(newborn==NULL)
	{
		printf("\nout of memory\n");
		exit(0);
	}
	return newborn;
		
}

/***************************************************************************
*Function			: nodefree
*Description		: Function to free the memory allocted to the node
*					  which is pointed by temp
*Input parameters	: Node Pointer temp 
*	
*RETURNS			:no value
*	
***************************************************************************/

void nodefree(NODEPTR temp)
{
	free(temp);
}

/***************************************************************************
*Function			: fnAddrecord
*Description		: Function to Add record 
*Input parameters	:Pointer which pointes to the header node
*	
*RETURNS			:Pointer which pointes to the header node
*	
***************************************************************************/

NODEPTR fnAddrecord(NODEPTR head)
{
	NODEPTR temp,prev;
	temp=nodecreate();
	printf("\nEnter the date[DD/MM/YYYY]:");
	scanf("%s",temp->date);
	printf("\nEnter the time[HH:MM]:");
	scanf("%s",temp->time);
	printf("\nEnter the place:");
	scanf("%s",temp->place);
	printf("\nName:");
	scanf("%s",temp->name);
	getchar();
	printf("\nEnter the note:\n");
	fgets(temp->note,650,stdin);
  	fflush(stdin);
  	prev=head->llink;
	temp->llink=prev;
  	prev->rlink=temp;
  	temp->rlink=head;
  	head->llink=temp;
	head->count++;
	return head;
}

/***************************************************************************
*Function			: fnDeleterecord
*Description		: Function to delete record 
*Input parameters	: Pointer which pointes to the header node and 2 
*					  character strings,one represents date and another
*					  represents the time.
*RETURNS			: Pointer which pointes to the header node
*	
***************************************************************************/

NODEPTR fnDeleterecord(NODEPTR head,char d[11],char t[6])
{
	NODEPTR temp,first,prev,next;
	first=head->rlink;
	if(first==head)
	{
		printf("\nNo records found\n");
		return head;
	}
	while(first!=head)
	{
		if((strcmp(first->date,d)==0)&&(strcmp(first->time,t)==0))
		{
			temp=first;
			break;
		}
		first=first->rlink;
	}
	getchar();
  if(first==head)
  {
    printf("Record not found\n");
    return head;
  }
	printf("Record deleted is:\n");
	puts(temp->note);
	prev=temp->llink;
	next=temp->rlink;
	prev->rlink=temp->rlink;
	next->llink=prev;
	nodefree(temp);
	head->count--;
	return head;
}

/***************************************************************************
*Function			: fnDisplay
*Description		: function to display all the records
*Input parameters	:Pointer which pointes to the header node
*	
*RETURNS			:no value
*	
***************************************************************************/


void fnDisplay(NODEPTR head)
{
	NODEPTR first;
	first=head->rlink;
	if(first==head)
	{
		printf("No record found\n");
		return;
	}
	while(first!=head)
	{
			printf("\n%s\n%s\n%s\n%s\n",first->date,first->time,first->place,first->name);
			puts(first->note);
			first=first->rlink;	
	}
	return;
}

/***************************************************************************
*Function			: checkpassword
*Description		: Function to check password
*Input parameters	: a character string which represents the password 
*					  entered by the user
*RETURNS			: true if password matches
*					  otherwise false
***************************************************************************/

bool checkpassword(char str1[20])
{
	FILE *fp;
	char str2[20];
	fp=fopen("password.dat","r");
	fscanf(fp,"%s",str2);
	if(strcmp(str1,str2)==0)
	{
		fclose(fp);
		return true;
	}
	fclose(fp);
	return false;
}

/***************************************************************************
*Function			: fnsetpassword
*Description		: Fuction to set the password
*Input parameters	: no parameters
*	
*RETURNS			: no value
*	
***************************************************************************/


void fnsetpassword()
{
	FILE *fp;
	char str1[20];
	printf("\nEnter the  pasword(no space):");
	scanf("%s",str1);
	fp=fopen("password.dat","w");
	fprintf(fp,"%s",str1);
	fclose(fp);
	return;
}

/***************************************************************************
*Function			: fnresetpassword
*Description		: Fuction to reset the password
*Input parameters	: no parameters
*	
*RETURNS			: no value
*	
***************************************************************************/

void fnresetpassword()
{
	FILE *fp;
	char str1[20],str2[20];
	fp=fopen("password.dat","r");
	printf("\nEnter the previous password\n");
	scanf("%s",str2);
	fscanf(fp,"%s",str1);
	fclose(fp);
	if(strcmp(str1,str2)==0)
	{
		printf("\nEnter the new password\n");
		scanf("%s",str1);
		fp=fopen("password.dat","w");
		fprintf(fp,"%s",str1);
		fclose(fp);
		return;
	}
	printf("\nInvalid password\n");
	return;
}

/***************************************************************************
*Function			: fnEditrecord
*Description		: Function to Edit record
*Input parameters	: Pointer which pointes to the header node and 2 
*					  character strings,one represents date and another
*					  represents the time.
*RETURNS			: Pointer which pointes to the header node
*	
***************************************************************************/

NODEPTR fnEditrecord(NODEPTR head,char d[11],char t[6])
{
	NODEPTR temp,first;
	first=head->rlink;
	if(first==head)
	{
		printf("\nNo records found\n");
		return head;
	}
	while(first!=head)
	{
		if((strcmp(first->date,d)==0)&&(strcmp(first->time,t)==0))
		{
			temp=first;
			break;
		}
		first=first->rlink;
	}
	getchar();
  	if(first==head)
  	{
    	printf("Record not found\n");
    	return head;
  	}
  	printf("\nNow you can edit the details entered in this record");
	printf("\nEnter the place:");
	scanf("%s",temp->place);
	printf("\nName:");
	scanf("%s",temp->name);
	getchar();
	printf("\nEnter the note:\n");
	fgets(temp->note,650,stdin);
	return head;
}

/***************************************************************************
*Function			: fnViewrecord
*Description		: Function to view record
*Input parameters	: Pointer which pointes to the header node and 2 
*					  character strings,one represents date and another
*					  represents the time.
*RETURNS			: Pointer which pointes to the header node
*	
***************************************************************************/

NODEPTR fnViewrecord(NODEPTR head,char d[11],char t[6])
{
	NODEPTR temp,first;
	first=head->rlink;
	if(first==head)
	{
		printf("\nNo records found\n");
		return head;
	}
	while(first!=head)
	{
		if((strcmp(first->date,d)==0)&&(strcmp(first->time,t)==0))
		{
			temp=first;
			break;
		}
		first=first->rlink;
	}
	getchar();
  	if(first==head)
  	{
    	printf("Record not found\n");
    	return head;
  	}
  	printf("\n%s\n%s\n",temp->place,temp->name);
	puts(first->note);
	return head;
}

/***************************************************************************
*Function			: fnSearchrecord_name
*Description		: Function to search records using name 
*Input parameters	: Pointer which pointes to the header node and a 
*					  character string which represents name 
*	
*RETURNS			: Pointer which pointes to the header node
*	
***************************************************************************/

NODEPTR fnSearchrecord_name(NODEPTR head,char N[25])
{
	NODEPTR temp,first;
	int iN=0;
	first=head->rlink;
	if(first==head)
	{
		printf("\nNo records found\n");
		return head;
	}
	while(first!=head)
	{
		if((strcmp(first->name,N)==0))
		{
			temp=first;
			printf("\n%s\n%s\n%s\n%s\n",temp->date,temp->time,temp->place,temp->name);
			puts(temp->note);
			iN++;
		}
		first=first->rlink;
	}
	getchar();
  	if(iN==0)
  	{
    	printf("Record not found\n");
    	return head;
  	}
	return head;
}

/***************************************************************************
*Function			: fnNotification
*Description		: Function to display notification
*Input parameters	: Pointer which pointes to the header node
*	
*RETURNS			:Pointer which pointes to the header node
*	
***************************************************************************/

NODEPTR fnNotification(NODEPTR head)
{
	NODEPTR first,temp;
	time_t curtime;
	char strh[2],strD[2],strM[2],strY[4];
	int icount=0,recordhour,iD,iM,iY,systemhour;
	time(&curtime);
	struct tm *myTime=localtime(&curtime);
	first=head->rlink;
	if(first==head)
	{
		return head;
	}
	while(first!=head)
	{
		strD[0]=first->date[0];
		strD[1]=first->date[1];
		strM[0]=first->date[3];
		strM[1]=first->date[4];
		strY[0]=first->date[6];
		strY[1]=first->date[7];
		strY[2]=first->date[8];
		strY[3]=first->date[9];
		iD=atoi(strD);
		iM=atoi(strM);
		iY=atoi(strY);
		if(iD==myTime->tm_mday && iM==((myTime->tm_mon)+1) && iY==myTime->tm_year+1900)
		{
			strh[0]=first->time[0];
			strh[1]=first->time[1];
			recordhour=atoi(strh);
			systemhour=myTime->tm_hour;
			if(recordhour==systemhour)
			{
				icount++;
				if(icount==1)
				{
					printf("\n*****************NOTIFICATION*****************");
				}
				printf("\n%s\n%s\n%s\n%s\n",first->date,first->time,first->place,first->name);
				puts(first->note);
				
			}
		}
		
		first=first->rlink;
	}
	return head;
}
