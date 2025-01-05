#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <signal.h>

#define TIMEOUT 15

void handle_alarm(int signo) {
    printf("Timeout\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
 
    int loop = 1;
    char *userInput = NULL;
    size_t len = 0;
    pid_t pid;  

    signal(SIGALRM, handle_alarm);

    while(loop == 1){
        printf("wish$ ");

        alarm(TIMEOUT);

        if (getline(&userInput, &len, stdin) != -1) {
            
            alarm(0);
            userInput[strcspn(userInput, "\n")] = '\0';
        
            if(strcmp(userInput, "exit") == 0){
                loop = 0;
            
            } else {
                pid = fork();
                if(pid == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
            
                }else if (pid == 0) {
                    
                    execlp("/bin/sh", "sh", "-c", userInput, (char *) NULL);
                    perror("execlp");
                    exit(EXIT_FAILURE);

                }else {
                    wait(NULL);

                }
            
            }       
        }
        
    }


    free(userInput);
    return 0;
}