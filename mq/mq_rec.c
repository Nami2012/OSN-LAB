#include<fcntl.h>
#include <sys/stat.h>        
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>


int main(){

    mqd_t q2;

    q2 = mq_open("/mq",O_RDWR);

    if(q2 == -1){
        printf("Error");
    }
    struct mq_attr *attr;
    attr = malloc(sizeof(struct mq_attr));

    mq_getattr(q2,attr);
    
    char str[30];
    int pr;
    while(1){
        mq_receive(q2,str,attr->mq_msgsize,&pr);
        printf("Priority= %d",pr);
        printf("\nMessage = %s\n",str);
        }

}