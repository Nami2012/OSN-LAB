#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

struct msg_buffer{
    long msg_type;
    char msg_text[100];
}msg;

int main(){

    key_t key;
    int msgid;

    key = ftok("mqfile",65);
    msgid = msgget(key,0666 | IPC_CREAT);
    
    while(1){
    msgrcv(msgid,&msg,sizeof(msg),1,0);

    printf("Data Received is : %s \n",  
                    msg.msg_text);
    }
     msgctl(msgid, IPC_RMID, NULL);
}