#include<fcntl.h>
#include <sys/stat.h>        
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(){

    mqd_t q1;

    q1 = mq_open("/mq",O_CREAT|O_RDWR,0666,NULL);

    if(q1 == -1){
        printf("Error");
    }
    
    char str[30];
    int pr;
    while(1){
        printf("\nEnter Message: "); 
        scanf("%s",str); 
        printf("Enter Priority: "); 
        scanf("%d",&pr); 
        if(!strcmp(str,"exit"))
            break;


        mq_send(q1,str,strlen(str),pr);
    }
}