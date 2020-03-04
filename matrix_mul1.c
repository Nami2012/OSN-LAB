#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>


int ar1[6][6],ar2[6][6];
	int C[6][6];
	int r1,c1,r2,c2;	

struct thread_data{
	int  i,j;
	int sum;
};


void *multiply(void  *arg){
	 struct thread_data *data;
	 data = (struct thread_data *)arg;
	 data->sum =0;
     for(int k=0;k<r2;k++)
		 
		 {
		  
		  data->sum += ar1[data->i][k]*ar2[k][data->j];
         }
         C[data->i][data->j] = data->sum;
    
     pthread_exit(NULL);
}
	
int main(){
	
	srand(time(0));
	
	//matrix size

	int *ret;

	r1= rand()%3+1;
	c1= rand()%3+1;
	r2= c1;
	c2= rand()%3+1;
	int tid =0;
	
	
	//matrix values
	int val;
	
	//first matrix
	printf("\nfirst matrix \n");
	for(int i=0;i<r1;i++)
	   for(int j =0;j<c1;j++)
			{
				ar1[i][j] = rand()%5;
			} 
	for(int i=0;i<r1;i++)
			{ for(int j =0;j<c1;j++)
		{
				printf("%d ",ar1[i][j]);
			}
		printf("\n");}


	//second matrix		
	printf("\nsecond matrix \n");
	
	for(int i=0;i<r2;i++)
	   for(int j =0;j<c2;j++)
			{
				ar2[i][j] = rand()%5;
			} 
	for(int i=0;i<r2;i++)
			{ for(int j =0;j<c2;j++)
		{
			printf("%d ",ar2[i][j]);
			}
			printf("\n");
			}
		
	
	
	//thread creation
	
	pthread_t thread[r1*c2];
	
	for(int i=0;i<r1;i++)
	{
		for(int j=0;j<c2;j++)
		{   
            struct thread_data *t =(struct thread_data*) malloc(sizeof(struct thread_data));
            t->i = i;
		    t->j = j;
            pthread_create(&thread[tid++],NULL,multiply,(void *)t);   
	    }
    }
		 
         for(int i=0;i<tid;i++)
         {
		  pthread_join(thread[i],NULL);
		 }

	printf("\n");
	for(int i=0;i<r1;i++)
		{ for(int j =0;j<c2;j++)
	{
		printf("%d ",C[i][j]);
		}
		printf("\n");
		}
		
	


	
	

	return 0;
}
