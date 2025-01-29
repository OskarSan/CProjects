#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grepStream(FILE *stream, const char *searchTerm) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stream)) != -1) {
        if (strstr(line, searchTerm) != NULL) {
            printf("%s", line);
        }
    }

    free(line);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
       
        printf("my-grep: searchterm [file ...]\n"); // No search term specified -> print message and exit with status code 1
        return 1;
    }

    const char *searchTerm = argv[1];

    if (argc == 2) {
        // No files specified so read from stdin
        grepStream(stdin, searchTerm);
    } else {
        for (int i = 2; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                
                printf("my-grep: cannot open file\n");// Error opening file print message and exit with status code 1
                return 1;
            }

            grepStream(file, searchTerm);
            fclose(file);
        }
    }

    return 0;// Return 0 -> ran successfully
}