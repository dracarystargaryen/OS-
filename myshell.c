#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


void Cmd(char *cmds, char** param);
int execCmd(char** param);

#define MAX_LENGTH 150
#define MAX_PARAMS 10

int main(){
    char cmds[MAX_LENGTH + 1];
    char* param[MAX_PARAMS + 1];

    int countCmd = 0;

    while(1){
        char* user = getenv("User");
        printf("%s@shell %d>", user, ++countCmd);

        if(fgets(cmds, sizeof(cmds), stdin) == NULL) break;

        if(cmds[strlen(cmds) -1] == '\n'){
            cmds[strlen(cmds)-1] = '\0';
        }

        Cmd(cmds, param);

        if(strcmp(param[0], "exit") == 0) break;

        if(execCmd(param) == 0) break;
    }
    return 0;
}

void Cmd(char* cmds, char** param){
    for(int j = 0; j < MAX_PARAMS; j++){
        param[j] = strsep(&cmds, " ");
        if(param[j] == NULL) break;
    }
}

int execCmd(char** param){
    pid_t pid = fork();

    if( pid == -1){
        char* err = strerror(errno);
        printf("fork: %s\n", err);
        return 1;
    }
    else if (pid == 0){
        execvp(param[0], param);

        char* err = strerror(errno);
        printf("shell: %s: %s\n", param[0], err);
        return 0;
    }

    else{
        int childProcess;
        waitpid(pid, &childProcess, 0);
        return 1;
    }
}