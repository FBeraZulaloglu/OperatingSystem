// topla ve cikarı çagıracak olan program 
// 3 parametre alarak çalışmalıdır.
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/wait.h> 

int main(int argc, char *argv[],char **envp){
    
    pid_t p = fork();
    char *newargv[2];
    int result;
    newargv[0] = argv[1];
    newargv[1] = argv[2];
    if(p == 0){
        if(strcmp(argv[0],"cikar")){
            execve("./cikar",newargv,envp);
        }
        else if(strcmp(argv[0],"topla")){
            execve("./topla",newargv,envp);
        }
    }
    else if(p > 0){
        wait(&result);
    }
    
    return result;
}