#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct c
{
	int n;
	int flag;
}chit;

typedef struct p
{
	chit card[5][5];
	int count;
	char name[30];
}player;

void playergame();
int generatenum(int,player*);
void computer();
void fillcomp();
void fillplayer(player*);
void search(int,player*);
void display(player*);
int checkplayer(player*);

void main()
{
	int choice;
	system("clear");
	printf("\n\n\n\n\t\t\t WELCOME TO B-I-N-G-O \n\n\t\t 1) Player V/S Player? \n\n\t\t 2) Player V/S Computer? \n\n\t\t Enter your choice : ");
	scanf("%d",&choice);
	choose : 
	if(choice == '1')
		playergame();
	else
		if(choice == '2')
			computer();
		else
			printf("\n Invalid Choice . Please try again. ");
			goto choose;
}

void display(player *p)
{
	int i,j;
	for(i=0; i<5; i++)
	{
		for(j=0; j<5; j++)
		printf(" %d ",p->card[i][j].n);
		
		printf("\n");
	}
}
	

void fillplayer(player *p)
{
	int i,j,num;

	for(i=0; i<5; i++)
	{
		for(j=0; j<5; j++)
		{
			printf("\n Enter number on %d row, %d column of the your card : ",i+1,j+1);	
			scanf("%d",&num);
			p->card[i][j].n = num;
			p->card[i][j].flag = 0;
		}
	}
	system("clear");
	printf("\n Thank you. Your card is : \n");
	display(p);
}

void search(int num, player *p)
{
	int i,j;
	for(i=0 ; i<5; i++)
	{
		for(j=0; j<5; j++)
		{
			if(p->card[i][j].n == num)
			{
				p->card[i][j].flag = 1;
				break;
			}
		}
	}
}

int checkplayer(player *p)
{
	int i,j,rcount,ccount,dcount1 = 0,dcount2 = 0;
	p->count = 0;
	for(i=0 ; i<5 ; i++)
	{
		rcount = ccount = 0;
		for(j=0 ; j<5 ; j++)
		{
			if(p->card[i][j].flag == 1)
			rcount++;
			if(p->card[j][i].flag == 1)
			ccount++;
			if(i == j)
			{
				if(p->card[i][j].flag == 1)
				dcount1++;
				if(p->card[i][4-j].flag == 1)
				dcount2++;
			}
		}
		if(rcount == 5)
			p->count++;
		if(ccount == 5)
			p->count++;
	}

	if(dcount1 == 5)
		p->count++;
	if(dcount2 == 5)
		p->count++;

	if(p->count == 5)
		return 1;
	else
		return 0;

}
		

void playergame()
{
	player p1, p2;
	int num,status;
	char choice;
	system("clear");
	printf("\n Player1, What is your name?\n");
	scanf("%s",p1.name);
	printf("\n Okay %s, let's begin. Please enter numbers on your card : \n", p1.name);
	fillplayer(&p1);

	system("clear");
	printf("\n Player2, What is your name?\n");
	scanf("%s",p2.name);
	printf("\n Okay %s, let's begin. Please enter numbers on your card : \n", p2.name);
	fillplayer(&p2);

	system("clear");
	printf("\n Let's begin B-I-N-G-O \n ");

	while(1)
	{
		status = checkplayer(&p1);
		if(status == 1)
		{
			system("clear");
			printf("\n %s WON!! Congratulations! ",p1.name);
			exit(0);
		}
		status = checkplayer(&p2);
		if(status == 1)
		{
			system("clear");
			printf("\n %s WON!! Congratulations! ",p2.name);
			exit(0);
		}

		printf("\n %s, Do you want to see your card?(Y/N) ", p1.name);
		scanf("%c",&choice);
		if(choice == 'Y' || choice == 'y')
			display(&p1);

		printf("\n %s, Do you want to see your card?(Y/N) ", p2.name);
		scanf("%c",&choice);
		if(choice == 'Y' || choice == 'y')
			display(&p2);

		printf("\n %s, Enter your number : ", p1.name);
		scanf("%d", &num);
		search(num,&p1);
		search(num,&p2);

		printf("\n %s, Enter your number : ", p2.name);
		scanf("%d", &num);
		search(num,&p1);
		search(num,&p2);
		
	}
}

int generatenumber(int num,player *c)
{
	int n,i,j;

	gen : 
	n = rand() % 25;
	for(i=0; i<5; i++)
		for(j=0; j<5; j++)
			if(c->card[i][j].n == n)
				if(c->card[i][j].flag == 1)
					goto gen;
	return n;
}

int doesexist(int n, player *c)
{
	int i, j;
	for(i=0; i<5; i++)
	{
		for(j=0; j<5; j++)
		{
			if(c->card[i][j].n == n)
				return 1;
		}
	}
	return 0;
}

void fillcomp(player *c)
{
	int n, i,j, status;
	for(i = 0; i<5 ; i++)
	{
		for(j = 0; j<5; j++)
		{
			gen :
			n = rand() % 25;
			status = doesexist(n,c);
			if(status)
				goto gen;
			else
				c->card[i][j].n = n;
		}
	}
}			

void computer()
{
	player p, comp;
	int num,status;
	char choice;
	
	system("clear");
	printf("\n What is your name? \n");
	scanf("%s",p.name);
	printf("\n Okay %s, let's begin. Please enter numbers on your card : ",p.name);
	fillplayer(&p);

	fillcomp(&comp);

	system("clear");
	printf("\n Let's play B-I-N-G-O! \n");

	while(1)
	{
		status = checkplayer(&p);
		if(status == 1)
		{
			system("clear");
			printf("\n %s WON!! Congratulations! ",p.name);
			exit(0);
		}
		status = checkplayer(&comp);
		if(status == 1)
		{
			system("clear");
			printf("\n COMPUTER WON!!");
			exit(0);
		}
	
		printf("\n %s, Do you want to see your card?(Y/N) ", p.name);
		scanf("%c",&choice);
		if(choice == 'Y' || choice == 'y')
			display(&p);
	
		printf("\n %s, Enter your number : ", p.name);
		scanf("%d", &num);
		search(num,&p);
		search(num,&comp);
	
		num = generatenum(num,&comp);
		printf("\n The computer has entered : %d \n",num);
		search(num,&p);
		search(num,&comp);
	}
}
