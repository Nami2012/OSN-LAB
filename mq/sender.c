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
    
    msg.msg_type = 1;
    while(1){
        fgets(msg.msg_text,100,stdin);
        msgsnd(msgid,&msg,sizeof(msg),0);
        sleep(1);
        if(!strcmp(msg.msg_text,"exit"))
            break;
    }


}