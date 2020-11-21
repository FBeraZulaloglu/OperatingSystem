#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/wait.h> 
#include<sys/types.h>

#define MAXPARAM 100

int main(int argc, char *argv[]){
    //printf("ISLEM : %s\n",argv[0]);
    //printf("NUMBERS : %s,%s\n",argv[1],argv[2]);
    
    int stat,result;
    char **newargv = (char **)malloc(MAXPARAM*sizeof(char *));

    for (int i = 0; i < MAXPARAM; i++)
    {
        newargv[i] = (char *)malloc(MAXPARAM* sizeof(char));
    }
    strcpy(newargv[0],argv[1]); // cikar or topla
    strcpy(newargv[1],argv[2]);
    
    pid_t p = fork();
    if(p == 0){
        if(!strcmp(argv[0],"cikar")){
            stat = execv("./cikar",newargv);
            perror("cikar : execv failed\n");
        }
        else if(!strcmp(argv[0],"topla")){
            stat = execv("./topla",newargv);
            perror("topla : execv failed\n");
        }
    }
    else if(p > 0){
        wait(&stat);
        result = WEXITSTATUS(stat);
    }
    
    return result;
}