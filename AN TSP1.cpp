#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<limits.h>
#include<iostream>
using namespace std;
 int originalGraph[10000][1000];
 int points[10000][2],n;
 int curr_path[10000];
 int new_path[10000];
 int min_path[10000];
 int visited[10000],cost=0;
//clock_t start_t,end_t, total_t;
int generateRandomNumber()
{
	return (rand()%(n-1))+1;
}
int generateRandomNumber1()
{
	return (rand()%(100-1))+1;
}
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
{   points[i][0]=generateRandomNumber1();
    points[i][1]=generateRandomNumber1();
printf("\nEnter Elements of Row # : %d\n",i+1);
	printf("%d %d",points[i][0],points[i][1]);
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
/*void print()
{
printf("the array List=\n");
for(int i=0;i<=n;i++)
	{
	  printf("%d\t",curr_path[i]);
	}
	printf("\n");

	for(int i=0;i<=n;i++)
	{
	printf("%d\t",new_path[i]);
	}
	printf("\n");


	for(int i=0;i<=n;i++)
	{
		printf("%d\t",min_path[i]);
	}
	printf("\n");	
}*/
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
//	print();
	
	
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
	//swap(r1,r2,new_path);
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
		cost+=originalGraph[path[i]][path[(i+1)%n]];
	}
	return cost;
}
void retraceMinPath(int *min_path)
{
   //cout<<"time="<<total_t<<endl;
   printf("The shortest cost obtained For SA is=%d\n",getCost(min_path));
   printf("Tour sequence For SA=");
  for(int i=0;i<n;i++)
   printf("%d-->",min_path[i]+1);
  printf("%d",min_path[0]+1);
  printf("\n");
}
int least(int c)
{
long long	int i,nc=9999999;
long long	int min=9999999,kmin;
	for(i=0;i < n;i++)
	{
		if((originalGraph[c][i]!=0)&&(visited[i]==0))
		{
		
			if(originalGraph[c][i] < min)
			{
				min=originalGraph[i][0]+originalGraph[c][i];
			//	kmin=originalGraph[c][i];
			//	nc=i;
			}
			kmin=originalGraph[c][i];
				nc=i;
		}
	}
	if(min!=9999999)
		cost+=kmin;
	return nc;
}
void mincost(int city)
{
	/*start_t=clock();
	cout<<"\nstart="<<start_t<<endl;*/
	int i,ncity;
	visited[city]=1;	
	printf("%d -->",city+1);
	ncity=least(city);
	if(ncity==9999999)
	{
		ncity=0;
		printf("%d",ncity+1);
		cost+=originalGraph[city][ncity];
	
		/*	end_t=clock();
			cout<<"\nend="<<end_t<<endl;
			double total1 = ((double)(end_t - start_t))/CLOCKS_PER_SEC;
            printf("\nTotal time taken by CPU: %.20f\n", total1  );*/
            	return;
	}
	mincost(ncity);
}
void put()
{
	//printf("\nTime taken: %.200000fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	printf("\n\nMinimum cost For DP:=");
	printf("%d",cost);
}
int main()
{
srand(time(NULL));
get();
int r1,r2;
clock_t start_t,end_t, total_t;
clock_t start_t1,end_t1, total_t3;
double random_number,prob,gain;
double temperature=100000000000000;
double absoluteTemperature=1;
init();
start_t=clock();
cout<<"Start For SA="<<start_t<<endl;
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
   
    two_opt(r1, r2, new_path);

    gain=getCost(new_path) - getCost(curr_path);
   
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
    // end_t = clock(); 
    // cout<<"end="<<end_t<<endl;
     
    //retraceMinPath();
    }
    /*else
    {
    	printf("\nThere is no path of minimum distance\n");
	}*/
   }
   temperature*=0.01;
  }
  retraceMinPath(min_path);
  end_t = clock();
  cout<<"End For SA="<<end_t<<endl;
 double total1 = ((double)(end_t - start_t))/CLOCKS_PER_SEC;
   printf("Total time taken by CPU For SA: %.20f\n", total1  );

  //Minimum distance using dynamic prog.
 // get();
	start_t1=clock();
	cout<<"\nstart for DP="<<start_t1<<endl;
	printf("\n\n Path For DP:\n\n");
	mincost(0);
	end_t1=clock();
	cout<<"\nend For DP="<<end_t1<<endl;
	double total2 = ((double)(end_t1 - start_t1))/CLOCKS_PER_SEC;
   printf("\nTotal time taken by CPU For SA: %.20f\n", total2  );
	put();


return 0;
}
