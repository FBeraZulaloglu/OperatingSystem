#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 

int main(int argc, char *argv[]){
    
    for (int i = 0; i < atoi(argv[1]); i++)
    {
        printf("%s\n",argv[0]);
    }
    //printf("TEKRAR PROGRAMI ÇALIŞIYOR...");
    return 0;
}