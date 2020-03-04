#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

#include<sys/wait.h>

int countwords(char *str,int ssize){
     int count = 0, i;
    int size = strlen(str);
    for (i = 0;i<size;i++)
    {
        if ((str[i] == ' ' && str[i+1] != ' ') || str[i]==',' || (str[i] =='.'&&str[i]!=' ') ||(str[i] =='\n')  )
            count++;    
    }
    if(str[size-1] != ' ' )
        count++;
    
    if(str[size-1] == '\n' )
        count--;
    return count;
}

int countch(char *str,int ssize){
     int count = 0, i;
      int size = strlen(str);
    for (i = 0;i<size;i++)
    {
        if (str[i] == ' ' || str[i] == '\n')
            continue;
        count++;    
    }
        return count;
    }


int countlines(char *str,int ssize){
     int count = 1, i;
      int size = strlen(str);
    for (i = 0;i<size;i++)
    {
        if (str[i] == '\n')
            count++;    
    }
    if (str[size-1] == '\n')
        count--;    
    
        return count;
    }
void rand_string(char *str,int size){
    char string[] = "ab \ncd \n efgh\nabcd \nefghijkl \n \n mnopq rstuvw xyzABCDE FGHIJKLMNOPQRS TUVW\n XYZ0 1234 \n 56789,.-#'?! ";
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
          char *ptr = (char *) malloc(100 * sizeof(char));
          rand_string(ptr,size);
          printf("Enter Message:");
          scanf("%[^\t]",ptr);
	      printf("Generated string : %s ",ptr);
          
          //fprintf(stdout,"\n Generated string : %s \n",ptr);
          //write to pipe
          write(p[1], ptr, 100); 
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
	       	char *str = (char *) malloc(100 * sizeof(char));
            int nbytes;

            read(p[0], str, 100);
            close(p[0]);

            printf("\n Received String: %s\n", str); 
            


            //count characters and words         
            int ch =countch(str,size);
            int w  = countwords(str,size);
            int lines = countlines(str,size);
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
                

                fprintf(fptr,"\n characters = %d;",ch);
                fprintf(fptr,"\n words = %d;",w);
                 fprintf(fptr,"\n lines = %d;",lines);
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