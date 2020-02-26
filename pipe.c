#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#include<sys/wait.h>

int countwords(char *str,int size){
     int count = 0, i;
 
    for (i = 0;i<size;i++)
    {
        if ((str[i] == ' ' && str[i+1] != ' ') || str[i]==',' || (str[i] =='.'&&str[i]!=' '))
            count++;    
    }
    if(str[size-1] != ' ')
        count++;
    return count;
}
int countch(char *str,int size){
     int count = 0, i;
 
    for (i = 0;i<size;i++)
    {
        if (str[i] == ' ')
            continue;
        count++;    
    }
        return count;
    }
void rand_string(char *str,int size){
    char string[] = "abcd  ef ghabcdefghijklmnopq rstuvw xyzABCDEFGHIJKLMNOPQRS TUVWXYZ0 123456789,.-#'?! ";
    for(int i=0;i<size;i++){
       str[i] = string[rand()%strlen(string)];
    }
}

int main(){
    srand(time(0));
    int size = rand()%25 +1;
    int p[2],pr[2]; 


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
          char buf[128];
          char *ptr = (char *) malloc(size * sizeof(char));
          rand_string(ptr,size);
	      printf("Generated string : %s",ptr);
          
          //write to pipe
          write(p[1], ptr, size); 
          close(p[1]);
          
          //read from pipe
          wait(NULL);
          int nbytes;
          read(pr[0], buf,128);
          printf("\n %s",buf);
	    }
	
    else if(pid==0)
		{
            //read string from pipe
	       	char *str = (char *) malloc(size * sizeof(char));
            int nbytes;
            read(p[0], str, size);
            printf("\nReceived String: %s\n", str); 
            close(p[0]);


            //count characters and words         
            int ch =countch(str,size);
            int w  = countwords(str,size);
        
            //write into file
            FILE *fptr;
            fptr = fopen("stringcharacteristics.txt","w");
            if(fptr==NULL)
            {
                //cannot open
                printf("Error!");
                exit(1);

             }

            else{
                

                fprintf(fptr,"\n characters = %d",ch);
                fprintf(fptr,"\n words = %d",w);
                fclose(fptr);
         
   
            }

            //read from file
            char buf[128],res[128]="";
            fptr = fopen("stringcharacteristics.txt","r");
            while(fscanf(fptr,"%s",buf)==1)
                { 
                  strcat(res," ");
                  strcat(res,buf);
                }
               write(pr[1], res, sizeof(res)); 
                 
                printf("\n ");
            fclose(fptr);
            close(pr[1]);
            exit(0);
		}
	
}