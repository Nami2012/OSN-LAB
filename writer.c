#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include <unistd.h>
#include <string.h>

struct message {
    char msg[1000];
    int flag;
};

int main(){

    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    struct message *str = (struct message*) shmat(shmid,(void *)0,0);
    
    while(1){
        
        fgets(str->msg,1000,stdin);
        str->flag =1;
        sleep(1);
        if(!strcmp(str->msg,"exit"))
            break;
    }
    shmdt(str);

    return 0;
}