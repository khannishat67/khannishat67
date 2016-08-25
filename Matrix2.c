#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
int mat[100][100];
float head[4],sum[4]={0};
int ctr[4]={0};
FILE *fp;
	
void initialise()	//Initialise Function
{
	int i,j;
	int arr[100]={0};
	fp = fopen("abc.txt","r");
	if(fp == NULL)
	printf("Cannot open file");
	for(i=0;i<100;i++)	//Initialisation of a 10x10 Matrix
	{
		for(j=0;j<100;j++)
		{
			
			fscanf(fp,"%d ",&mat[i][j]);
		}
	}
	
	fclose(fp);
	srand(getpid());
	for(i=0;i<4;i++)	//Initialisation of 4 random head numbers
	{
		int x= rand()%1000+1;
		if(arr[x-1] == 0)
		{	
			head[i] = rand()%200;
			arr[x-1]=1;
			sum[i] = head[i];
		}
		else
		i--;
	
	}
	
}
void display() //Displaying of the Matrix and heads
{
	int i,j;
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
			printf("%3d ",mat[i][j]);
		printf("\n");
	}
	for(i=0;i<4;i++)
	printf("%.3f ",head[i]);
	printf("\n");
}
int closest(int n)
{
	int min=9999,pos=-1,k;
	for(k=0;k<4;k++)	//Checking the closest head corresponding to mat[i][j]
	{
		int x = abs(head[k]-n);
		if(x<min)
		{
			min = x;
			pos = k;
		}
	}
	return pos;
}			
void calculate()	//Calculation of new heads
{
	int i,j,c;
	for(i=0;i<4;i++)		//Infinite loop bug fixed. I had forgot to initialise the sum 
	{
		sum[i]=head[i];
		ctr[i]=1;
	}

	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			c = closest(mat[i][j]);
			sum[c]=sum[c]+mat[i][j];
			ctr[c]++;
		}
	}
	for(i=0;i<4;i++)
	{
		head[i]=sum[i]/ctr[i]; 		//Calculation of new Head which is the average of the sum of the matrix elements
		printf("%f ",head[i]);
	}
	printf("\n");
	
}
int isSame(float b[],float c[])		//checking whether the present head is equal to the old head values
{
	int i,f=1;
	for(i=0;i<4;i++)
		if(b[i]!=c[i])
		f=0;
	return f;
}
void changeMatrix()		//Function to change the actual matrix with the values of position of head
{
	int i,j,k;
	
	fp = fopen("write.txt","w");
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)		//caught the error! was running the i loop instead of j in nested
		mat[i][j] = closest(mat[i][j]);
	}
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		fprintf(fp,"%d ",mat[i][j]);
		fprintf(fp,"\n");
	}
	fclose(fp);
}
int main(void)		//Main Function
{
	int i,k=0;
	float b[4];
	initialise();
	display();
	
	do
	{
		for(i=0;i<4;i++)
			b[i] = head[i];
		calculate();
		k++;
	}while(!isSame(b,head));	//Loop will run unless the values of head stop changing
	printf("Total Iterations : %d\n",k);
	changeMatrix();	
	display();	
}
