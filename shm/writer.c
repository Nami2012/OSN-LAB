#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include <unistd.h>
#include <string.h>

int main(){

    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *str = (char *) shmat(shmid,(void *)0,0);
    
    while(1){
        fgets(str,1000,stdin);
        sleep(1);
        if(!strcmp(str,"exit"))
            break;
    }
    shmdt(str);

    return 0;
}