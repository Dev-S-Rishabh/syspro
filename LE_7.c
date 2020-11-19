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
void delet();
void print();

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
			case 'p' : print();
				break ;
			case 'a' : append();
				break;
			case 'd' : delet();
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

void print()
{
	for(temp=head;temp!=NULL;temp=temp->next)
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

void delet()
{
	char t;
	int n;
	sscanf(cmd,"%c%d",&t,&n);
	if(n==1)
	{
		temp=head;
		head=head->next;
		free(temp);
	}
	else
	{
		last=head;
		while(n>2)
		{
			last=last->next;
			if(last==NULL)
			{
				printf("\n Invalid line number");
				return;
			}
			n--;
		}
		temp=last->next;
		last->next=temp->next;
		free(temp);
	}
}





