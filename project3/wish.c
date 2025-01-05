#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <signal.h>


int main(int argc, char *argv[]) {
 
    int loop = 1;
    char *userInput = NULL;
    size_t len = 0;
    pid_t pid;  
    char *path[] = {"/bin", "usr/bin", NULL};

    while(loop == 1){
        printf("wish$ ");

      
        if (getline(&userInput, &len, stdin) != -1) {
       
            userInput[strcspn(userInput, "\n")] = '\0';
        
            if(strcmp(userInput, "exit") == 0){
                loop = 0;
            
            } else {
                pid = fork();
                if(pid == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
            
                }else if (pid == 0) {
                    
                     char command[256];
                    int found = 0;
                    for (int i = 0; path[i] != NULL; i++) {
                        snprintf(command, sizeof(command), "%s/%s", path[i], userInput);
                        if (access(command, X_OK) == 0) {
                            execlp(command, userInput, (char *) NULL);
                            perror("execlp");
                            exit(EXIT_FAILURE);
                        }
                    }
                    if (!found) {
                        fprintf(stderr, "Command not found: %s\n", userInput);
                        exit(EXIT_FAILURE);
                    }
                }else {
                    wait(NULL);

                }
            
            }       
        }
        
    }


    free(userInput);
    return 0;
}