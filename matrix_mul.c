#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>


struct thread_data{
	int  first;
	int second;
};


void *multiply(void  *arg){
	 struct thread_data *data;
	 data = (struct thread_data *)arg;
	 int first = data->first;
	 int second = data->second;
	 
	 pthread_exit(&first);
}
	
int main(){
	struct thread_data t;
	srand(time(0));
	void *ret;
	int r1,c1,r2,c2;
	r1= rand()%2+1;
	c1= rand()%2+1;
	r2= c1;
	c2= rand()%2+1;
	int val;
	int ar1[r1][c1],ar2[r2][c2];
	int C[r1][c2];
	printf("\nfirst matrix \n");
	for(int i=0;i<r1;i++)
	   for(int j =0;j<c1;j++)
	{
		ar1[i][j] = rand()%10;
		} 
	for(int i=0;i<r1;i++)
		{ for(int j =0;j<c1;j++)
	{
		printf("%d",ar1[i][j]);
		}
	printf("\n");}	
	printf("\nsecond matrix \n");
	
	for(int i=0;i<r2;i++)
	   for(int j =0;j<c2;j++)
	{
		ar2[i][j] = rand()%10;
		} 
	for(int i=0;i<r2;i++)
		{ for(int j =0;j<c2;j++)
	{
		printf("%d",ar2[i][j]);
		}
		printf("\n");
		}
		
	
	
	
	pthread_t t1;
	
	for(int i=0;i<r1;i++)
	{
		for(int j=0;j<c2;j++)
		{ C[i][j]=0;
		 for(int k=0;k<c1;k++)
		 
		 {
		  t.first = ar1[i][k];
		  t.second = ar2[k][j];
		  pthread_create(&t1,NULL,multiply,(void *)&t);
		 pthread_join(t1,&ret);
		 int *ptr = (int *)ret;
		 C[i][j] = *(int *)ptr;
		  //printf("\n %d",ret);
		
	
		 }
	
	     }
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
