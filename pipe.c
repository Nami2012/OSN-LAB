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
void rand_string(char *str,int size)
{
    char string[] = "abcd  ef ghabcdefghijklmnopq rstuvw xyzABCDEFGHIJKLMNOPQRS TUVWXYZ0 123456789,.-#'?! ";
    for(int i=0;i<size;i++){
       str[i] = string[rand()%strlen(string)];
    }
}

int main(){
    srand(time(0));
     int size = rand()%256 +1;
         
         int p[2],pr[2]; 
              if (pipe(p) < 0) 
              exit(1); 
           
              if (pipe(pr) < 0) 
              exit(1); 
   
	pid_t pid;
	pid = fork();	
	
    if(pid>0){
          char *ptr = (char *) malloc(size * sizeof(char));
          rand_string(ptr,size);
	      printf("%s",ptr);
              write(p[1], ptr, size); 
              close(p[1]);
        wait(NULL);
            
   
	}
	else if(pid==0)
		{

	       	char *str = (char *) malloc(size * sizeof(char));
                int nbytes;
        read(p[0], str, size);
            printf("\n \n \n%s\n", str); 
        close(p[0]);
         
        int ch =countch(str,size);
        int w  = countwords(str,size);
        
        FILE *fptr;

        fptr = fopen("stringcharacteristics.txt","w");
        if(fptr==NULL)
        {
            //cannot open
               printf("Error!");
               exit(1);

        }
        
        else{
            printf("\n characters == %d",ch); 
       
          printf("\n words == %d",w); 
       fprintf(fptr,"\n characters = %d",ch);
          
          fprintf(fptr,"\n characters = %d",ch);
          fprintf(fptr,"\n words = %d",w);
          
          fclose(fptr);
   
        }
       

		}
	
	

		
	
	
}