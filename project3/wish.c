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

void execute_command(char *userInput, char **path) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        char command[256];
        for (int i = 0; path[i] != NULL; i++) {
            snprintf(command, sizeof(command), "%s/%s", path[i], userInput);
            if (access(command, X_OK) == 0) {
                execlp(command, userInput, (char *) NULL);
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        }
        fprintf(stderr, "Command not found: %s\n", userInput);
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    int loop = 1;
    char *userInput = NULL;
    size_t len = 0;
    char *path[256] = {"/bin", NULL};

    signal(SIGALRM, handle_alarm);

    while (loop == 1) {
        printf("wish$ ");
        alarm(TIMEOUT);

        if (getline(&userInput, &len, stdin) != -1) {
            alarm(0);
            userInput[strcspn(userInput, "\n")] = '\0';

            // Tokenize user input
            char *token = strtok(userInput, " ");
            if (token == NULL) {
                continue;
            }

            // Handle built-in commands
            if (strcmp(token, "exit") == 0) {
                if (strtok(NULL, " ") != NULL) {
                    fprintf(stderr, "exit: too many arguments\n");
                } else {
                    exit(0);
                }
            } else if (strcmp(token, "cd") == 0) {
                char *dir = strtok(NULL, " ");
                if (dir == NULL || strtok(NULL, " ") != NULL) {
                    fprintf(stderr, "cd: wrong number of arguments\n");
                } else if (chdir(dir) != 0) {
                    perror("cd");
                }
            } else if (strcmp(token, "path") == 0) {
                int i = 0;
                while ((token = strtok(NULL, " ")) != NULL) {
                    path[i++] = token;
                }
                path[i] = NULL;
            } else if (strcmp(token, "curpath") == 0) {
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    printf("%s$ \n", cwd);
                } else {
                    perror("getcwd");
                    exit(EXIT_FAILURE);
                }

            } else {
                // Execute external command
                execute_command(userInput, path);
            }
        }
    }

    free(userInput);
    return 0;
}