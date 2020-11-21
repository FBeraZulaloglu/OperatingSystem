#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

#define clear() printf("\033[H\033[J") 
#define MAXPARAM 100
#define numberOfCommands 4

void init_shell(void);

int takeCommands(void);

int executeCommand(char *);

int commandHandler(char **);

int parameterControl(char *,char *,int);

int isNumeric(char *);

char *myStrCpy(char *destination,char *source);

int main(int argc, char *argv[]) 
{  
    init_shell(); 

    while(1){
        if(takeCommands() != -1) continue;
        else break;
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

int takeCommands(){
    char *buffer;
    buffer = readline("\nmyshell>> ");
    
    char *commands[MAXPARAM];
    int i = 0;
    commands[i] = strsep(&buffer,"|");
    while(commands[i] != NULL){
        //printf("COMMAND(%d) :%s \n",i,commands[i]);
        executeCommand(commands[i]);
        i++;
        commands[i] = strsep(&buffer,"|");
    }
    
    return 0;
}

int executeCommand(char* c){
    if(strlen(c) != 0)
    {
        add_history(c);
        char **commandList = (char **)malloc(MAXPARAM*sizeof(char *));

        for (int i = 0; i < MAXPARAM; i++)
        {
            commandList[i] = (char *)malloc(MAXPARAM* sizeof(char));
        }
        
        char *command;
        int i = 0;
        commandList[i] = strsep(&c," ");
        while(commandList[i] != NULL)
        {
            i++;
            commandList[i] = strsep(&c," ");
        }

        if(!strcmp(commandList[0],"exit")){
            printf("shell program finished! \n");
            return -1;
        }
        else{
            if(commandHandler(commandList)==-1){
                printf("Yanlis bir komut girdiniz.\n");
            }
        }
    }
    return 0;
}

int commandHandler(char **commandParams)
{
    char* shellList[numberOfCommands];
    // All commands in my shell
    shellList[0] = "islem";
    shellList[1] = "tekrar";
    shellList[2] = "clear";
    shellList[3] = "cat";
    // switchArg decides witch commands to works
    int switchArg = -1;
    for (int i = 0; i < numberOfCommands; i++)
    {
        if(!strcmp(commandParams[0],shellList[i])){
            switchArg = i;
            //printf("-- komut sistemde bulundu/command has found in the system--\n");
            break;
        }
    }
    if(switchArg == -1){
        // there is no command to run
        return -1;
    }
    
    if(switchArg == 0){
        // to control the correctness of necessary parameters
        if(parameterControl(commandParams[2],commandParams[3],switchArg) == -1){
            return -1;
        }

        int finalResult,stat;
        char **newargv = (char **)malloc(MAXPARAM*sizeof(char *));

        for (int i = 0; i < MAXPARAM; i++)
        {
            newargv[i] = (char *)malloc(MAXPARAM* sizeof(char));
        }
        myStrCpy(newargv[0],commandParams[1]); // cikar or topla
        myStrCpy(newargv[1],commandParams[2]);
        myStrCpy(newargv[2],commandParams[3]);

        pid_t p = fork();
        if(p == 0){
            stat = execv("./islem",newargv);
            perror("islem : execv failed\n");
        }
        else if (p > 0){
            wait(&stat);
            finalResult = WEXITSTATUS(stat);
            printf("ISLEM RESULT IS : %d\n",finalResult);
        }
    }
    else if(switchArg == 1)
    {
        // tekrar program will run
        
        if(parameterControl(commandParams[1],commandParams[2],switchArg)==-1){
            return -1;
        }
        char **newargv = (char **)malloc(MAXPARAM*sizeof(char *));

        for (int i = 0; i < MAXPARAM; i++)
        {
            newargv[i] = (char *)malloc(MAXPARAM* sizeof(char));
        }
        
        myStrCpy(newargv[0],commandParams[1]); 
        myStrCpy(newargv[1],commandParams[2]);

        // tekrar islemi yapılacak ve iki parametre alcaktır.
        pid_t p1 = fork();
        if(p1 == 0){
            execv("./tekrar", newargv);
        }
        else{
            // DONT USE WAİT HERE !!
        }

    }
    else if(switchArg == 2){
        clear();
    }
    else if(switchArg == 3){
        char *newargv[MAXPARAM] = {NULL};
        newargv[0]="cat";
        newargv[1] = commandParams[1];
        newargv[2] = NULL;
        pid_t p2 = fork();
        if(p2==0){
            execv("/bin/cat",newargv);
        }
    }
    
    return 0;
}

int parameterControl(char *p, char *p1,int commandNo){
    if(commandNo == 0){
        // islem komutu
        if(p == NULL || p1 == NULL || isNumeric(p) == -1 || isNumeric(p1)==-1){
            return -1;
        } 
    }
    else if(commandNo == 1){
        // tekrar komutu
        if(p == NULL || p1 == NULL || isNumeric(p1)==-1)
            return -1;
    }
}

int isNumeric(char *number){
    int i =0;
    while(number[i] != '\0')
    {
        if(!isdigit(number[i])){
            return -1;
        }
        i++;
    }
    return 0;
}

char *myStrCpy(char *destination,char *source){
    int i = 0;
    char *start = destination;
    while(*source != '\0'){
        *destination = *source;
        destination++;
        source++;
        i++;
    }
    *destination = '\0';
    return start;
}

