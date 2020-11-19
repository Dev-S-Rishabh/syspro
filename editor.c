//Program to implement Line Editor
#include <stdio.h>
//#include <conio.h>
//#include <alloc.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define NEWNODE (struct node *)malloc(sizeof(struct node))
struct node
{
char line[80];
struct node *next;
}*start=NULL,*end=NULL;
int n=0;

FILE * fp1;

int gettcount(char str[],char *delimit)
{
char *s;
int ct=0;
s=strtok(str,delimit);
while(s!=NULL)
{
	ct++;
	s=strtok(NULL,delimit);
}
return ct;
}

void loadfile()
{
while(!feof(fp1))
{
	if(start==NULL)
		start=end=NEWNODE;
	else
	{
		end->next=NEWNODE;
		end=end->next;
	}
	end->next=NULL;
	n++;
	fgets(end->line,80,fp1);
	if(end->line[strlen(end->line)-1]!='\n')
		strcat(end->line,"\n");
}
}

void printline(int n1,int n2)
{
struct node *t1;
int i;
if(n1==0)
{
	for(t1=start;t1!=NULL;t1=t1->next)
		printf("%s",t1->line);
}
else if((n1>0)&&(n1<=n))
{
	for(i=1,t1=start;i<n1;t1=t1->next,i++);
	if(n2==0)
	{
		for(;t1!=NULL;t1=t1->next)
			printf("%s",t1->line);
	}
	else
	{
		for(;i<=n2;i++,t1=t1->next)
			printf("%s",t1->line);
	}
}
}

void addlines(int n1)
{
struct node *st1=NULL,*last=NULL,*t1;
int ct=0,i;
char str[80];
gets(str);
while(str[0]!='.')
{
	if(st1==NULL)
		st1=last=NEWNODE;
	else
	{
		last->next=NEWNODE;
		last=last->next;
	}
	last->next=NULL;
	strcpy(last->line,strcat(str,"\n"));
	ct++;
	gets(str);
}
if(n1==0)
{
	if(start==NULL)
		start=st1;
	else
		end->next=st1;
	end=last;
	n=n+ct;
}
else if(n1<=n)
{
	if(n1==1)
	{
		last->next=start;
		start=st1;
	}
	else
	{
		for(i=1,t1=start;i<n1-1;t1=t1->next,i++);
		last->next=t1->next;
		t1->next=st1;
	}
	n=n+ct;
}
}

void searchfile(int n1,int n2)
{
struct node *t1;
int i;
char pattern[80];
printf("\nEnter Pattern : ");
gets(pattern);
if((n1>0)&&(n1<=n2)&&(n2<=n))
	for(i=1,t1=start;i<n1;t1=t1->next,i++);
if(n1==0)
{
	for(t1=start;t1!=NULL;t1=t1->next)
	{
		if(strstr(t1->line,pattern)!=NULL)
			printf("%s",t1->line);
	}
}
else
{
	for(;i<=n2;t1=t1->next,i++)
	{
		if(strstr(t1->line,pattern)!=NULL)
			printf("%s",t1->line);
	}
}
}

void savefile()
{
char fname[13];
struct node *t1;
printf("\nEnter FileName : ");
gets(fname);
fp1=fopen(fname,"w");
if(fp1!=NULL)
{
	for(t1=start;t1!=NULL;t1=t1->next)
	{
		if(t1->next==NULL)
			t1->line[strlen(t1->line)-1]='\0';
		fprintf(fp1,"%s",t1->line);
	}
	fclose(fp1);
}
}

void deleteline(int n1,int n2)
{
struct node *t1,*t2,*t3;
int i;
if((n1>0)&&(n2==0))
{
	if(n1==1)
	{
		t1=start;
		start=start->next;
	}
	else
	{
		for(i=1,t2=start;i<n1-1;t2=t2->next,i++);
		t1=t2->next;
		t2->next=t1->next;
	}
	if(start==NULL)
		end=NULL;
	else if(n1==n)
		end=t2;
	free(t1);
	n--;
}
else if((n1<n2) && (n2<=n))
{
	if(n1==1)
		t3=start;
	else
	{
		for(i=1,t2=start;i<n1-1;t2=t2->next,i++);
		t3=t2->next;
		if(n2==n)
			end=t2;
	}
	for(i=1;i<=(n2-n1+1);i++)
	{
		t1=t3;
		t3=t3->next;
		free(t1);
		n--;
	}
	if(n1==1)
		start=t3;
	else
		t2->next=t3;
}
}

void copyline(int n1,int n2,int n3)
{
struct node *t1,*t2,*t3,*st1=NULL,*last;
int i;
if(((n1>0)&&(n2>=0)&&(n3>0))&&((n1<=n)&&(n2<=n)&&(n3<=n+1)))
{
	for(i=1,t1=start;i<n1;t1=t1->next,i++);
	for(i=1,t2=start;i<n3-1;t2=t2->next,i++);
	if(n2==0)	//copying single line
	{
		t3=NEWNODE;
		strcpy(t3->line,t1->line);
		if(n3==1)
		{
			t3->next=start;
			start=t3;
		}
		else
		{
			t3->next=t2->next;
			t2->next=t3;
		}
		if(n3==n+1)
			end=t3;
		n++;
	}
	else if(n1<n2)	// copying range of lines
	{
		for(i=1;i<=(n2-n1+1);i++)
		{
			if(st1==NULL)
				st1=last=NEWNODE;
			else
			{
				last->next=NEWNODE;
				last=last->next;
			}
			strcpy(last->line,t1->line);
			t1=t1->next;
		}
		if(n3==1)
		{
			last->next=start;
			start=st1;
		}
		else
		{
			last->next=t2->next;
			t2->next=st1;
		}
		if(n3==n+1)
			end=last;
		n=n+n2-n1+1;
	}
}
}


void help()
{
	printf("Enter");
	printf("\n p			-	Print all lines");
	printf("\n p m n		-	Print range of lines");
	printf("\n a			-	Append");
	printf("\n d n		-	Delete line Number n");
	printf("\n d m n		-	Delete range of lines from m to n");
	printf("\n c n1 n2		-	copy line n1 at n2 position");
	printf("\n c n1 n2 n3	   -	copy range of lines from n1 to n2 at n3 position");
	printf("\n i n			-	Insert lines at position n");
        printf("\n f  n1 n2		-	Search given pattern in given range");

	printf("\n q			-	Quit");

}
 main(int argc,char *argv[])
{
char cmd[80],str1[80],arglist[4][10];
int i,tcount,n1,n2,n3;

if(argc<=2)
{
	if(argc==2)
	{
		fp1=fopen(argv[1],"r");
		if(fp1==NULL)
		{
			printf("\nFile Not Exist !");
			exit(0);
		}
		loadfile();
		fclose(fp1);
	}
	while(1)
	{
		n1=n2=n3=0;
		printf("\n$ ");
		gets(cmd);
		strcpy(str1,cmd);
		tcount=gettcount(str1," ");
		strcpy(arglist[0],strtok(cmd," "));
		for(i=1;i<tcount;i++)
			strcpy(arglist[i],strtok(NULL," "));
		if((tcount==1) && (strcmp(arglist[0],"q")==0))
			break;
		else if((tcount==1) && strcmp(arglist[0],"h")==0)
			help();
		else if((tcount==1) && (strcmp(arglist[0],"p")==0) && (start!=NULL))
			printline(n1,n2);
		else if((tcount==1) && (strcmp(arglist[0],"a")==0))
			addlines(n1);
		else if((tcount==1) && (strcmp(arglist[0],"f")==0) && (start!=NULL))
			searchfile(n1,n2);
		else if((tcount==1) && (strcmp(arglist[0],"s")==0) && (start!=NULL))
			savefile();
		else if((start!=NULL)&&(strcmp(arglist[0],"c")!=0))
		{
			if(tcount==2)
				n1=atoi(arglist[1]);
			else if(tcount==3)
			{
				n1=atoi(arglist[1]);
				n2=atoi(arglist[2]);
			}
			if(strcmp(arglist[0],"p")==0)
				printline(n1,n2);
			else if(strcmp(arglist[0],"d")==0)
				deleteline(n1,n2);
			else if(strcmp(arglist[0],"f")==0)
				searchfile(n1,n2);
			else if(strcmp(arglist[0],"i")==0)
				addlines(n1);
		}
		else if((start!=NULL)&&((strcmp(arglist[0],"c")==0)))
				
		{
			if(tcount==3)
			{
				n1=atoi(arglist[1]);
				n3=atoi(arglist[2]);
			}
			else if(tcount==4)
			{
				n1=atoi(arglist[1]);
				n2=atoi(arglist[2]);
				n3=atoi(arglist[3]);
			}
			if(strcmp(arglist[0],"c")==0)
				copyline(n1,n2,n3);
			;
		}
	}
}
}