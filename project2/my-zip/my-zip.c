#include <stdio.h>
#include <stdlib.h>

// Function for compressing the contents of a file
void compressFile(FILE *file, int *count, int *previousChar) {
    int currentChar = EOF; 

    // Read characters from the file until end of file
    while ((currentChar = fgetc(file)) != EOF) {
        if (currentChar == *previousChar) {
            // If the current character is the same as the previous one increment count variable
            (*count)++;
        } else {
            // If the current character is different write the count and the letter to stdout
            if (*count > 0) {
                fwrite(count, sizeof(int), 1, stdout);
                fputc(*previousChar, stdout);
            }
            // Update previousChar to the current character and reset count
            *previousChar = currentChar;
            *count = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if at least one file is provided
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }

    int count = 0; // Initialize count to 0
    int previousChar = EOF; // Initialize previousChar to EOF

    // Loop through each file provided as an argument
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r"); // Open the file in read mode
        if (file == NULL) {
            // If the file cannot be opened print an error message and return 1
            printf("my-zip: cannot open file\n");
            return 1;
        }

        // Compress the contents of the file
        compressFile(file, &count, &previousChar);
        fclose(file); // Close the file
    }

    // Write the remaining count and character to stdout
    if (count > 0) {
        fwrite(&count, sizeof(int), 1, stdout);
        fputc(previousChar, stdout);
    }

    return 0; // Return 0 -> ran successfully
}