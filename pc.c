#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>

pthread_t *producers;
pthread_t *consumers;

sem_t mutex, empty,full;

int *buf,bufpos=-1,pc,cc,bufsize;

int produce(pthread_t self){
    int i=0;
    int p = 1+rand()%20;

    while(!pthread_equal(*(producers+1),self) && i<pc)
        i++;
    
    printf("Producer %d produced %d \n\n",i+1,p);
    return p;
}

void consume(int p,pthread_t self){
    int i=0;
    while(!pthread_equal(*(consumers + i),self) && i<cc)
        i++;

        printf("buffer status:");

        for(int i=0;i<=bufpos;i++){
            printf("%d ",*(buf+i));
        }
    printf("\n Consumer %d consumed %d",i+1,p);
}

void display_full(){

    printf("Cannot Insert to Buffer, Buffer is full\n");

}

void display_empty(){
    printf("Buffer is Empty, Cannot Consume.\n");


}


void *producer(void *arg){
   while(1){
        int p = produce(pthread_self());
        ++bufpos;
        if(bufpos>=bufsize)
        {
            display_full();
            sleep(5+rand()%5);
            --bufpos;
            continue;
        }

        sem_wait(&empty);
        sem_wait(&mutex);
       
        *(buf+bufpos) = p;
        
        sem_post(&mutex);
        sem_post(&full);

        sleep(5 + rand()%5);
    }
}


void* consumer(void *arg){
    int c;

    while (1)
    {
        if(bufpos<=-1)
        {
            display_empty;
            sleep(3+rand()%4);
            continue;
        }
        sem_wait(&full);
        sem_wait(&mutex);

        c = *(buf+bufpos);
        consume(c,pthread_self());
        --bufpos;

        sem_post(&mutex);
        sem_post(&empty);
        sleep(3+rand()%5);

    }
    return NULL;
    

}

int main(){

    int err;
	srand(time(0));

    //initialize semaphore;

    sem_init(&mutex,0,1);
    sem_init(&full,0,0);

    //read count

    pc = rand()%20 +1;
    printf("\n Number of Producers are: %d",pc);
    producers = (pthread_t*)malloc(pc*sizeof(pthread_t));

    cc = rand()%20 +1;
    printf("\n Number of consumers are: %d",cc);
    consumers = (pthread_t*)malloc(cc*sizeof(pthread_t));
    
    bufsize = rand()%30 + 1;
    printf("\n BufferSize: %d",bufsize);
    buf = (int*)malloc(bufsize*sizeof(int));


    sem_init(&empty,0,bufsize);

    for(int i=0;i<pc;i++){
        //create producer threads
        pthread_create(producers+i,NULL,&producer,NULL);
    }

    for(int i=0;i<cc;i++){
        //create consumer threads
        pthread_create(consumers+i,NULL,&consumer,NULL);
        
        
    }


    for(int i=0;i<pc;i++){
        pthread_join(*(producers+i),NULL);
    }

    for(int i=0;i<cc;i++){

        //join consumer threads

        pthread_join(*(consumers+i),NULL);
    }



    

}