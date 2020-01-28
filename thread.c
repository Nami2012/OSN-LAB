#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>


struct thread_data{
	int  num;
	long *array;
	int  half;
};


void *sort(void  *arg){
	 struct thread_data *data;
	 data = (struct thread_data *)arg;
	 int size = data->num;
	 long *array = data->array;
	 int half = data->half;
	 int temp;
	 
	 if(half == 1)
		{ for(int i=0;i<size/2-1;i++)
			for(int j=0;j<size/2-i-1;j++)
			{
				if(array[j]>array[j+1]){
					temp = array[j];
					array[j] = array[j+1];
					array[j+1] = temp;
				}
			}
		}
	 if(half == 1)
		{ for(int i=0;i<size/2-2;i++)
			for(int j=0;j<size/2-i-2;j++)
			{
				if(array[j]>array[j+1]){
					temp = array[j];
					array[j] = array[j+1];
					array[j+1] = temp;
				}
			}
		}
		
	else if(half == 2)
		{ int k=0;
			for(int i=size/2;i<size-1;i++)
			{
			for(int j=size/2;j<size-k-1;j++)
			{	
				if(array[j]>array[j+1]){
					temp = array[j];
					array[j] = array[j+1];
					array[j+1] = temp;
				}
				
			}
		
		k++;}
		}
	 
}
	
int main(){
	struct thread_data t[2];
	srand(time(0));
	long num;
	num= rand()%10+1;
	printf("Total Elements: %ld",num);
	long ar[num];
	printf("\nNumbers \n");
	for(int i=0;i<num;i++)
	{
		ar[i] = rand()%10;
		} 
	for(int i=0;i<num;i++)
	{
		printf("%ld",ar[i]);
		}
	t[0].num =num;
	t[0].array = ar;
	t[0].half = 1;	
	
	t[1].num =num;
	t[1].array = ar;
	t[1].half = 2;	
	
	pthread_t t1,t2;
	
	pthread_create(&t1,NULL,sort,(void *)&t[0]);
	pthread_create(&t2,NULL,sort,(void *)&t[1]);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	
	printf("\n");
	for(int i=0;i<num;i++)
	{
		printf("%ld",ar[i]);
		}

	return 0;
}
