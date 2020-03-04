#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#include<sys/wait.h>

void rand_string(char *str,int size){
    char string[] = "abcdefghabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    for(int i=0;i<size;i++){
       str[i] = string[rand()%strlen(string)-rand()%5];
    }
    str[size-1]='\0';
}

char *concat(char * s1,char*s2){
    int size = strlen(s1)+strlen(s2);
    char *res = (char *) malloc(size * sizeof(char));
    int s1size = strlen(s1);
    int j=0;
    for(int i=0;i<s1size;i++){
        res[j++] = s1[i];
    }
     for(int i=0;i<strlen(s2);i++){
        res[j++] = s2[i];
        
    }
    res[size] = '\0';

    return res;
}
int main(){
    srand(time(0));
    
    int p[2],pr[2]; 
    int size = rand()%25 +1;
    int size1 = rand()%12 +1;

    //pipe system call
    if (pipe(p) < 0) 
        exit(1); 
           
    if (pipe(pr) < 0) 
        exit(1); 
   
    //process generation
	pid_t pid;
	pid = fork();	
	
    if(pid>0){//parent process
          
          
          //string generation
          char buf[size+size1];
    
          char *ptr = (char *) malloc(size * sizeof(char));

          rand_string(ptr,size);
	    
          printf("first string: %s \n",ptr);
          
          //write to pipe
          write(p[1], ptr, size); 
          close(p[1]);
          
          //read from pipe
          wait(NULL);
          int nbytes;
          read(pr[0], buf,size+size1);
            close(pr[0]);
          printf("concatenated string :%s \n",buf);
	    }
	
    else if(pid==0)
		{
            //read string from pipe
	       	char *str = (char *) malloc(size * sizeof(char));
            int nbytes;
            read(p[0], str, size);
            printf("first string received : %s \n", str); 
            close(p[0]);
            
            //random string generation
            char buf[128];
          
            char *tr = (char *) malloc(size1 * sizeof(char));
            rand_string(tr,size1);
	        printf("second string: %s\n",tr);
          
            char *res =  (char *) malloc((size1+size) * sizeof(char));
            res =  concat(str,tr);
            write(pr[1], res, size+size1); 
            printf("\n ");
            close(pr[1]);
            exit(0);
		}
	
}