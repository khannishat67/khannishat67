#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>

int x[5]={-1,-1,-1,-1,-1},y[5]={-1,-1,-1,-1,-1},z[5]={0};
char a[10][11];
int ctr[10]={0};

void initialise()	//Function To Initialise the strings
{
	int i=0,j=0;
	srand(getpid());
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			a[i][j]=(rand()%2 +48);
		a[i][j]='\0';
	}
	
}
void display()		//Function to display the strings
{
	int i,j;
	for(i=0;i<10;i++)
		printf("%d : %s \n",i,a[i]);  
	printf("\n\n\n");  
}
void dieOut(int n)	//Function to kill a string
{
	char die[]="0000000000";
	strcpy(a[n],die);
	ctr[n]=0;
}
void evaluateSolutions()	//Function to evaluate the generated solutions
{
	int i,j,c;
	for(i=0;i<10;i++)	
	{
		for(j=0;j<10;j++)	//selecting those having more than 5 1s
		{
			if(a[i][j]=='1')
				ctr[i]++;
		}
	}
	for(i=0;i<10;i++)
		printf("%d ",ctr[i]);
	printf("\n");

	for(i=0;i<10;i++)	//removing the weaker species
	{
		if(ctr[i]<5)
			dieOut(i);
	}
	display();
	
	while(1)
	{
		c = rand()%10;
		if(ctr[c]!=0)
		break;
	}
	printf("\n %d\n",c);
	for(i=0;i<10;i++)
	{
		if(ctr[i]==0)
			strcpy(a[i],a[c]);
	}
	
}
int isOptimumSolution()	//Checking whether it is an optimum solution or not if not then return 1
{
	int i,c=0;
	for(i=0;i<10;i++)
	{
		if(strcmp(a[i],"1111111111")==0)
		c++;
	}
	if(c==10)
	return 1;
	return 0; 
}
int chk(int n,int j,char ch)	//Function to remove repitition
{
	int i,p,q;
	if(ch=='x')
	{
		for(i=0;i<j;i++)
		{
			if(n==x[i])
				return 1;
		}
		for(i=0;i<5;i++)
		{
			if(n==y[i])
				return 1;
		}
	}
	else
	{
		for(i=0;i<5;i++)
		{
			if(n==x[i])
				return 1;
		}
		for(i=0;i<j;i++)
		{
			if(n==y[i])
				return 1;
		}
	}
	return 0;
}
void selection()	//Function to select Species
{
	int i;
	for(i=0;i<5;i++)
	{
		x[i]=rand()%10;
		if(chk(x[i],i,'x'))
		{
			x[i]=0;
			i--;
			continue;
		}
		y[i]=rand()%10;
		if(chk(y[i],i,'y'))
		{
			y[i]=0;
			i--;
			continue;
		}
		z[i]=rand()%10;
	printf("%d %d %d\n",x[i],y[i],z[i]);
	}	


}
void crossover()	//Function to perform crossover
{
	int i,j;	
	char tmp;
	for(i=0;i<5;i++)
	{
	for(j=z[i];j<10;j++)
	{
		tmp=a[x[i]][j];
		a[x[i]][j]=a[y[i]][j];
		a[y[i]][j]=tmp;
	}
	}
	for(i=0;i<10;i++)
	ctr[i]=0;

}
void mutation()		//Function to perform mutation
{
	int i,j;
	i=rand()%11;
	j=rand()%11;
	if(a[i][j]=='0')
	{
		a[i][j]='1';
		printf("Mutated %d in %d\n",j,i);
		display();
	}
}		
int main()	//Algorithm Implemented as shown in the pdf :)
{
	int i=0;
	initialise();
	display();
	evaluateSolutions();
	
	display();
	do{
	
		selection();
		
		crossover();
		display();
		mutation();

		i++;
	}
	while(!isOptimumSolution());
	if(isOptimumSolution()!=0)
	printf("Number of iterations= %d\n",i);
	return 0;
}
