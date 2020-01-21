#include<stdio.h>
#include <unistd.h> 


void main(){
	
	int num;
	int fact = 1,x=1;
	pid_t pid;

	scanf("%d",&num);
	pid = fork();	
	if(pid==0){
		
	        for(int i=1;i<=num;i++)	{
	        	fact *=i;
			printf(" %d",fact);
	       }	
	
	}
	else if(pid>0)
		{
		
	       	for(int i=1;i<=num;i++)	{
	        	fact *=i;
	        }
			
               	printf("factorial(%d):%d \n",num,fact);
  		
		}
	
	

		
	
		
	
}
