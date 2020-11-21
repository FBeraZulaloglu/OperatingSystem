#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 

int main(int argc, char *argv[]){
    int sub = atoi(argv[0])-atoi(argv[1]);
    //printf("SUB = %d :",sub);
    return sub;
}