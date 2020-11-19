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
void print();
void deletmn();
void insert();
void save();

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
			case 's' : save();
				break;
			case 'd' : deletmn();
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

void deletmn()
{
	char t;
	int m,n,ntoken;
	NODE *ml,*nl;
	ntoken=sscanf(cmd,"%c %d %d",&t,&m,&n);
	if(ntoken==1)
	{
		printf("\nError:No line number..");
		return;
	}
	else if(ntoken==2)
	{
		n=m;
	}
	else if(m>n)
	{
		printf("\nFrom line should be less than toline");
		return;
	}
	temp=NULL;
	ml=head;
	for(i=1;i<m;i++)
	{
		temp=ml;
		ml=ml->next;
	}
	nl=head;
	for(i=1;i<n;i++)
	{
		nl=nl->next;
	}
	if(ml==head)
	{
		head=nl->next;
	}
	else
	{
		temp->next=nl->next;
	}
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




