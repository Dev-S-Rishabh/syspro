#include<stdio.h>
#include<conio.h>
#include<alloc.h>
#include<string.h>

typedef struct node
{
	char *line;
	struct node *next;
}NODE;

NODE *head=NULL, *last, *temp;
char cmd[80];
int i;

NODE* loadfile(char[]);
void append();
void display();
void insert();

void main(int argc, char *argv[])
{
      if(argc==2)
      {
		head = loadfile(argv[1]);
      }
      else
      {
		head=NULL;
      }
      while(1)
      {
		printf("\n $ ");
		gets(cmd);
		switch (cmd[0])
		{
			case 'p' : display();
				break;
			case 'a' : append();
				break;
			case 'i' : insert();
				break;
			case 'e' : exit(0);
		}
      }
}

NODE* loadfile(char fname[])
{
	FILE *fp;
	head = NULL;
	fp = fopen(fname,"r");
	if(fp==NULL)
	{
		printf("\n File not found");
		return(head);
	}
	while(!feof(fp))
	{
		fgets(cmd,80,fp);
		temp = (NODE*)malloc(sizeof(NODE));
		temp->line = (char*)malloc(strlen(cmd));
		strcpy(temp->line,cmd);
		if(head==NULL)
		{
			head = temp;
		}
		else
		{
			last->next = temp;
		}
		last = temp;
	}
	temp->next = NULL;
	return (head);
}

void display()
{
	char t;
	int n1,n2;
	sscanf(cmd,"%c%d%d",&t,&n1,&n2);
	temp = head;
	for(i=1;i<n1;temp=temp->next,i++);
	for(i=n1;i<=n2;temp=temp->next,i++)
	{
		printf("%s",temp->line);
	}
}

void append()
{
	NODE* atop=NULL;
	char t,t1,str[80];
	sscanf(cmd,"%c%c%s",&t,&t1,&str);
	strcat(str,"\n");
	atop=(NODE*)malloc(sizeof(NODE));
	atop->line=(char*)malloc(strlen(str));
	strcpy(atop->line,str);
	for(temp=head;temp->next!=NULL;temp=temp->next);
	temp->next=atop;
	atop->next=NULL;
}

void insert()
{
	NODE *atop;
	char t,str[80];
	int n;
	int ntoken=sscanf(cmd,"%c %d %s",&t,&n,&str);
	strcat(str,"\n");
	atop=(NODE*)malloc(sizeof(NODE));
	atop->line=(char*)malloc(strlen(str));
	strcpy(atop->line,str);
	if (ntoken==1)
	{
		 printf("\nSpecify line number..");
		return;
	}
	temp=head;
	for(i=1;i<n-1;i++)
	{
		temp=temp->next;
		if(temp==NULL)
		{
			printf("Invalid line number..");
			return;
		}
	}

	if(n==1)
	{
		atop->next=head;
		head=atop;
	}
	else
	{
		atop->next=temp->next;
		temp->next=atop;
	}

}




