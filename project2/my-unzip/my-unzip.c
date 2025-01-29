#include <stdio.h>
#include <stdlib.h>

// Function to decompress the contents of a file
void decompressFile(FILE *file) {
    int count; // Variable to store the count of characters
    char character; // Variable to store character

    // Read the count and character from the file until end of file
    while (fread(&count, sizeof(int), 1, file) == 1) {
        character = fgetc(file); // Read the character
        // Print the character "count" times
        for (int i = 0; i < count; i++) {
            printf("%c", character);
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if at least one file is provided
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    // Loop through each file provided
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r"); // Open the file in read mode
        if (file == NULL) {
            // If the file cannot be opened print an error message and return 1
            printf("my-unzip: cannot open file %s\n", argv[i]);
            return 1;
        }

        // Decompress the contents of the file
        decompressFile(file);
        fclose(file); // Close the file
    }

    return 0; // Return 0 -> ran successfully
}