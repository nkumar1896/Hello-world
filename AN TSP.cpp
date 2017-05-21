#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<limits.h>
int originalGraph[40][40];
int points[40][2],n;
int	curr_path[20];
int new_path[20];
int min_path[20];
int calculateDistance(int x1,int y1,int x2,int y2)
{
		return int(sqrt(pow(x1-x2,2)+pow(y1-y2,2))+0.5);
}
void get()
{
printf("No of cities=");
scanf("%d",&n);
printf("\nEnter Cost Matrix\n");
for(int i=0;i<n;i++)
{   
printf("\nEnter Elements of Row # : %d\n",i+1);
	scanf("%d %d",&points[i][0],&points[i][1]);
}	

for(int i=0;i<n;i++)
{
			originalGraph[i][i]=0;
			for(int j=i+1;j<n;j++)
			{
				originalGraph[i][j]=calculateDistance(points[i][0],points[i][1],points[j][0],points[j][1]);
				originalGraph[j][i]=originalGraph[i][j];
			}
		}

printf("\n\nThe cost list is:\n\n");
	for(int k=0;k<n;k++)
		{
			printf("\n\n");
			for(int p=0;p<n;p++)
			{
					printf("\t%d",originalGraph[k][p]);
			}
		}
		printf("\n");
}
void print()
{
printf("the array List=\n");
for(int i=0;i<=n;i++)
	{
	  printf("%d\t",curr_path[i]);
	}
	printf("\n");
//int new_path[n+1];
	//new_path[0]=new_path[n]=0;
	for(int i=0;i<=n;i++)
	{
	printf("%d\t",new_path[i]);
	}
	printf("\n");

	//min_path[0]=new_path[n]=0;
	for(int i=0;i<=n;i++)
	{
		printf("%d\t",min_path[i]);
	}
	printf("\n");	
}
void init()
{
//int	curr_path[n+1];
	curr_path[0]=curr_path[n]=0;
	for(int i=1;i<n;i++)
	{
		curr_path[i]=i;
	}

//int new_path[n+1];
	new_path[0]=new_path[n]=0;
	for(int i=1;i<n;i++)
	{
		new_path[i]=i;
	}
//int	min_path[n+1];
	min_path[0]=new_path[n]=0;
	for(int i=1;i<n;i++)
	{
		min_path[i]=i;
	}
	print();
	
	
}
int generateRandomNumber()
{
	return (rand()%(n-1))+1;
}
void swap(int r1,int r2,int *new_path)
{
	int temp=new_path[r1];
	new_path[r1]=new_path[r2];
	new_path[r2]=temp;
}
void two_opt(int r1,int r2,int *new_path)
{
	int i,j,k,limit,temp;
	if(r1>r2)
	{
		temp=r1;
		r1=r2;
		r2=temp;
	}
	limit=floor((r2-r1+1)/2);
	i=r1,j=r2;
	for(k=0;k<limit+1;k++)
	{
		swap(i++,j--,new_path);
	}
}
int getCost(int *path)
{
	int cost=0;
	for(int i=0;i<n;i++)
	{
		cost+=originalGraph[path[i]][path[i+1]];
	}
	return cost;
}
void retraceMinPath()
{
	//printf("Time taken: %.2fs\n",(double)(clock()-tStart)/CLOCKS_PER_SEC);
	printf("The shortest cost obtained so far is=%d\n",getCost(min_path));
	printf("Tour sequence is=");
  for(int i=0;i<=n;i++)
   printf("%d\t",min_path[i]);
  printf("\n");
}
int main()
{
srand(time(NULL));
get();
int r1,r2;
double random_number,prob,gain;
double temperature=10000000000;
double absoluteTemperature=0.1;
init();
while(temperature>absoluteTemperature)
  {
   int i=100;
   while(--i)
   {
    for(int i=1;i<n;i++)
	{
		    
    new_path[i]=curr_path[i];  
    }

    r1=generateRandomNumber();
    r2=generateRandomNumber();
    // swap(r1, r2, new_path);
    two_opt(r1, r2, new_path);

    gain=getCost(new_path) - getCost(curr_path);
    //printf("Gain=%d",gain);
    random_number=(double) (rand()/ (double) RAND_MAX);

    prob=1/(1+ pow(M_E, (gain/temperature)));
    if(prob > 	random_number)
     for(int i=1;i<n;i++)    
       curr_path[i]=new_path[i];
    
   
    if(getCost(new_path) < getCost(min_path) )
    {
     for(int i=1;i<n;i++)
	 {
		   
      min_path[i]=new_path[i];
  }
      
     
    retraceMinPath();
    }
   }
   temperature*=0.9999;
  }


return 0;
}
