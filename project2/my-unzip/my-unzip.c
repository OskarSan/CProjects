/*
    AI USE STATEMENT
    Lassi Tuominen
    001119893

    Github Copilot was used for fixing and verifying 
    the syntax in the code, 
    as well as explaining some of the used functions end their parameters.

    Other AI tools were not used.

*/
#include <stdio.h>
#include <stdlib.h>

void decompressFile(FILE *file) {
    int count;
    char character;

    //Read the count and character from the file until end of file
    while (fread(&count, sizeof(int), 1, file) == 1) {
        character = fgetc(file);
        //Print the character "count" times
        for (int i = 0; i < count; i++) {
            printf("%c", character);
        }
    }
}

int main(int argc, char *argv[]) {
    //Check if at least one file is provided
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            //If the file cannot be opened print an error message and return 1
            printf("my-unzip: cannot open file %s\n", argv[i]);
            return 1;
        }

        decompressFile(file);
        fclose(file);
    }

    return 0; //Return 0 -> ran successfully
}