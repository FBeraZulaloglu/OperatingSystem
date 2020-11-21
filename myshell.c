// “adi_soyadi_no_opsis_proj1”
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

#define MAXCOM 1000
#define MAXLIST 1000

#define clear() printf("\033[H\033[J") 

void init_shell(void);

int takeCommand(char **);

int commandHandler(char **);

int main(int argc, char *argv[]) 
{ 
    char *inputString[MAXCOM], *parsedArgs[MAXLIST]; 
    //char* parsedArgsPiped[MAXLIST]; 
    int execFlag = 0; 
    init_shell(); 

    while(1){
        if(takeCommand(inputString) != -1){
            continue;
        }
        else{
            break;
        }
    }
    return 0; 
} 


void init_shell(){
    clear(); 
    printf("\n\n\n\n******************"
        "************************"); 
    printf("\n\n\n\t****MY SHELL****"); 
    printf("\n\n\t-WELCOME MY AWSOME WORLD-"); 
    printf("\n\n\n\n*******************"
        "***********************"); 
    char* username = getenv("USER"); 
    printf("\n\n\n USER is: @%s", username); 
    printf("\n"); 
    sleep(1); 
    clear();
}

int takeCommand(char **string){
    char *buffer;
    buffer = readline("\nmyshell>> ");

    // make string split ' '
    #pragma region split the input
    int i = 0;
    char *result = strtok(buffer," ");
    *(string+i) = result; 
    while(result != NULL){
        i++;
        result = strtok(NULL," ");
        *(string+i) = result;
    }
    // split has end
    #pragma endregion
    
    if(!strcmp(*(string),"exit")){
        return -1;
    }
    else{
        if(strlen(buffer) != 0)
        {
            if(commandHandler(string)==-1){
                printf("Komut bulunamamaktadır.\n");
            }
        }
        return 0;
    }
}

int commandHandler(char **command){
    int numberOfCommands = 4;
    char* commandList[numberOfCommands];
    int switchArg = -1;

    commandList[0] = "islem";
    commandList[1] = "tekrar";
    commandList[2] = "clear";

    for (int i = 0; i < numberOfCommands; i++)
    {
        if(!strcmp(*(command),commandList[i])){
            switchArg = i;
            //printf("-- komut sistemde bulundu/command has found in the system--\n");
            break;
        }
    }
    printf("switch arg %d",switchArg);
    if(switchArg == -1){
        return -1;
    }
    
    // decide which operator are you gonna use
    if(switchArg == 0){
        int finalResult;
        char *newargv[4];
        // (*command+1) is gonna decide whether sub or sum
        newargv[0] = *(command+1);
        newargv[1] = *(command+2);
        newargv[2] = *(command+3);
        newargv[3] = NULL;
        pid_t p = fork();
        if(p == 0){
            finalResult = execv("./islem",newargv);
            perror("islem : execv failed\n");
        }
        else if (p > 0){
            wait(&finalResult);
            printf("FINAL RESULT IS %d\n",WEXITSTATUS(finalResult));
        }
        //printf("(ISLEM) PARAM 1 : %s PARAM 2 : %s PARAM 3 : %s\n",*(command+1),*(command+2),*(command+3));
    }
    else if(switchArg == 1)
    {
        char *newargv[3];
        newargv[0] = *(command+1);
        newargv[1] = *(command+2);
        newargv[2] = NULL; // null koymassan parametre olarak gidemez
        // tekrar islemi yapılacak ve iki parametre alcaktır.
        pid_t p1 = fork();
        if(p1 == 0){
            printf("TEKRAR ÇALIŞIYOR\n");
            if(execv("./tekrar", newargv)==0){
                printf("(TEKRAR HAS COMPLETED)");
            }
        }
        else{
            // DONT USE WAİT HERE !!
        }

    }
    else if(switchArg == 2){
        clear();
        //execve("/bin/clear", newargv, envp);
    }
    
    
    
}
