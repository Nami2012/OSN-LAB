#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct message {
    char msg[1000];
    int flag;
};

int main(){

    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    struct message  *str = (struct message  *) shmat(shmid,(void *)0,0);
    
    while(1){
        if(str->flag==0)
            continue;
    
        if(!strcmp(str->msg,"NULL"))
            continue;
        if(!strcmp(str->msg,"exit"))
            break; 
        printf("\nMessage Received: %s\n",str->msg);
        str->flag =0;
        sleep(2);
    }

    shmdt(str); 
    
    shmctl(shmid,IPC_RMID,NULL);

    return 0;
}