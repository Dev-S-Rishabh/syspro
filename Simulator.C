#include<stdio.h>
#include<stdlib.h>

int reg[4],cc[6],lc,max,i;
long mem[1000],ireg;

void load();
void print();
void run();

main()
{
	char choice;
	while(1)
	{
		printf("\n a. Loading of the program from file into memory");
		printf("\n b. Printing the program loaded the memory");
		printf("\n c. Executing the loaded program");
		printf("\n e. Exit. \n");
		printf("\n Enter your choice : ");
		flushall();
		scanf("%c",&choice);

		switch(choice)
		{
		case 'a':load();
		      break;
		case 'b':print();
		      break;
		case 'c':run();
		      break;
		case 'e':exit(0);
		}
	}
}

void load()
{
	FILE *fp;
	char fname[30],buf[80];
	printf("\n Enter smac0 program file name : ");
	scanf("%s",fname);
	fp=fopen(fname,"r");
	if(fp==NULL)
	{
		printf("File does not exist.\n\n");
		return;
	}
	max=0;
	while(!feof(fp))
	{
		fscanf(fp,"%ld",&mem[++max]);
		fgets(buf,88,fp);
	}

	fclose(fp);

}

void print()
{
	for(i=1;i<=max;i++)
	printf("%06ld \n",mem[i]);
}

void run()
{
	int opc,opd1,opd2;
	lc=1;
	while(lc<=max)
	{
		ireg=mem[lc++];
		opc=ireg/10000;
		opd1=(ireg/1000)%10;
		opd2=ireg%1000;

		switch(opc)
		{
			case 1://add
			      reg[opd1]+=mem[opd2];
			      break;

			case 2://sub
			      reg[opd1]-=mem[opd2];
			      break;

			case 3://mult
			      reg[opd1]*=mem[opd2];
			      break;

			case 4://mover
			      reg[opd1]=mem[opd2];
			      break;

			case 5://movem
			      mem[opd2]=reg[opd1];
			      break;

			case 6://comp
			      for(i=1;i<=5;i++)  cc[i]=0;
			      if(reg[opd1]<mem[opd2])
				cc[1]=cc[2]=cc[6]=1;
			    else
			      if(reg[opd1]>mem[opd2])
				cc[4]=cc[5]=cc[6]=1;
			    else
				cc[2]=cc[3]=cc[5]=cc[6]=1;
			      break;

			case 7://bc
			      if(cc[opd1]==1)  lc=opd2;
			      break;

			case 8://div
			      reg[opd1]/=mem[opd2];
			      break;

			case 9://read
			      printf("\n Enter input : ");
			      scanf("%ld",&mem[opd2]);
			      break;

			case 10://print
			       printf("\n Output : %ld \n\n",mem[opd2]);
			       break;

			case 0:
				return;

		}
	}
}



