#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


void rand_string(char *str,int size)
{
    char string[] = "abcd ef ghabcdefghijklmnopq rstuvw xyzABCDEFGHIJKLMNOPQRS TUVWXYZ0 123456789,.-#'?! ";

    for(int i=0;i<size;i++){
       str[i] = string[rand()%strlen(string)];
       
    }
}

int main(){
    srand(time(0));
    int size = rand()%256 +1;
    char *ptr = (char *) malloc(size * sizeof(char));
    rand_string(ptr,size);
	 printf("%s",ptr);
}