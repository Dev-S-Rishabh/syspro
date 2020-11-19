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
void print();
void save();
void copy();

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
			case 's' : save();
				break;
			case 'c' : copy();
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

void save()
{
	FILE *fp=NULL;
	char fname[80];
	printf("\n Enter File name : ");
	gets(fname);
	fp = fopen(fname,"w");
	temp=head;
	while(temp!=NULL)
	{
		fputs(temp->line,fp);
		temp=temp->next;
	}
	fclose(fp);
	printf("\n File saved successfully");
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

void copy()
{
	NODE *head2=NULL,*last2,*temp2;
	int n,sno,eno;

	printf("\n Enter Starting & Ending Line Nos : ");
	scanf("%d%d",&sno,&eno);

	last=head;
	for(n=1;n<sno;n++)
	{
		last=last->next;
	}

	while(sno<=eno)
	{
		temp2 = (NODE*) malloc(sizeof(NODE));
		temp2->line=(char*)malloc(strlen(last->line));
		strcpy(temp2->line,last->line);
		temp2->next = NULL;

		if(head2==NULL)
		{
			head2=temp2;
		}
		else
		{
			last2->next = temp2;
		}
		last2 = temp2;
		last=last->next;
		sno++;
	}
	for(temp2=head2;temp2!=NULL;temp2=temp2->next)
	{
		printf(" %s ",temp2->line);
	}
}





