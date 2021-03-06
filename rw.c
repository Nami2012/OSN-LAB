#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>
pthread_t *reader,*writer;
int *buf,bufsize,bufpos=-1;
int r_count,w_count,rc_count=0;


sem_t mutex,rdr,wrt;

void display(){
        printf("\n buffer status:");
        for(int i=0;i<=bufpos;i++){
            printf("%d ",*(buf+i));
        }
}

void rd(int p){
    printf("\n read %d ",p);
}

void wr(){

 	 int p=rand()%20+1;
 	 ++bufpos;
 	 if(bufpos>=bufsize)
  		bufpos =0;
  	 *(buf+bufpos) = p;
	 display();

  
}

void* reader_create(void *args){
	int c; int i=0;
	while(!pthread_equal(*(reader+i),pthread_self()) && i<r_count)
        	i++;
	int p = i+1;
	while(1){
	
	if(sem_trywait(&mutex)==0){
	
	printf("\n \n Reader %d starts:",i);
	rc_count++;
	
	if(rc_count==1)
		sem_wait(&wrt);
	
	sem_post(&mutex);
	c=*(buf+bufpos);
	rd(c);
	sem_wait(&mutex);
	
	rc_count--;
	

	if(rc_count == 0)
		  sem_post(&wrt);
	{ printf("\n Reader %d End",i);}	
	sem_post(&mutex);

	}

	else{
	
		printf("\n reader %d cant write.semaphore already acquired",i);
	}
	sleep(rand()%10 + 1);
	}
}

void* writer_create(void *args){
	int i=0;
 	  while(!pthread_equal(*(writer+i),pthread_self()) && i<w_count)
       	 i++;
   
	while(1){
		
		if(sem_trywait(&wrt)==0){
		printf("\n \n Writer %d starts:",i+1);
		wr();
		printf("\n Writer %d End",i+1);
		sem_post(&wrt);}
		else{
		printf("\n writer %d cant write.semaphore already acquired",i);}
		sleep(rand()%10 + 1);
	}
	
}
int main(){
	srand(time(0));
	
	 //initialize values
	 	 r_count = rand()%20 +1;
    	 printf("\n Number of Readers are: %d",r_count);
    	 reader = (pthread_t*)malloc(r_count*sizeof(pthread_t));

    	 w_count = rand()%20 +1;
         printf("\n Number of writers are: %d",w_count);
         writer = (pthread_t*)malloc(w_count*sizeof(pthread_t));
    	
    	 bufsize = rand()%30 + 1;
    	 printf("\n BufferSize: %d",bufsize);
         buf = (int*)malloc(bufsize*sizeof(int));
    	
    	
         //semaphore initialisation
         
         sem_init(&mutex,0,1);
    	 sem_init(&rdr,0,0);
    	 sem_init(&wrt,0,1);
    	 
    	 //generate readers & writers
    	  for(int i=0;i<r_count;i++){
        	pthread_create(reader+i,NULL,&reader_create,NULL);
        	}

    	  for(int i=0;i<w_count;i++){
        	pthread_create(writer+i,NULL,&writer_create,NULL);
    		}


    	  for(int i=0;i<r_count;i++){
        	pthread_join(*(reader+i),NULL);
    		}

    	  for(int i=0;i<w_count;i++){
       		 pthread_join(*(writer+i),NULL);
       		 } 
       		 
    }
	
