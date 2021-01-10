#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>


int main(){
    int fd[2];
    int fd1[2];

    FILE *input = fopen("/Users/janehu/OneDrive/Visual Studio Code/editSource.txt", "r");
    char input_str[200];
    pid_t p;
    
    if(pipe(fd) == -1){
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    if (pipe(fd1) == -1){
        fprintf(stderr, "Pipe failed");
        return 1;
    }
    p = fork();
    if (p < 0){
        fprintf(stderr, "Fork has failed");
        return 1;
    }
    else if (p > 0){
        dup2(fd[0], 0);
        close(fd[0]);
        dup2(fd1[1], 1);
        close(fd1[1]);

        wait(NULL);
        



    }
    return 0; 
}