#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readString(FILE *file, char **buffer) {
    size_t size = 0;
    size_t capacity = 256;
    *buffer = (char *)malloc(capacity * sizeof(char));
    if (*buffer == NULL) {
        fprintf(stderr, "malloc failed");
        exit(1);
    }

    int ch;
    while ((ch = fgetc(file)) != EOF && ch != '\n') {
        if (size + 1 >= capacity) {
            capacity *= 2;
            *buffer = (char *)realloc(*buffer, capacity * sizeof(char));
            if (*buffer == NULL) {
                fprintf(stderr, "realloc failed");
                exit(1);
            }
        }
        (*buffer)[size++] = ch;
    }
    (*buffer)[size] = '\0';
}



struct Node {
    char* data;
    struct Node* next;
};



struct Node* createNode(char* data) {
    //printf("Creating node: %s\n", data);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = strdup(data);
    newNode->next = NULL;
    return newNode;
}

void insert(struct Node** head, char* data) {
    //printf("Inserting: %s\n", data);
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}


void traverseList(struct Node* head, char* file) {
    
    struct Node* temp = head;
    //printf("%s\n",file);
    if (file != NULL) {
        FILE *output = fopen(file, "w");
        if(output == NULL) {
            fprintf(stderr, "Unable to open file\n");
            return;
        }
        while (temp != NULL) {
            fprintf(output, "%s\n", temp->data);
            temp = temp->next;
        }
        fclose(output);
        return;
    }
    else {
        //printf("Traversing list: \n");

        while (temp != NULL) {
            printf("%s \n", temp->data);
            temp = temp->next;
        }
    }
    printf("\n");

}


int main( int argc, char *argv[] ) {

    FILE *file;
    char *buffer = NULL;
    struct Node* head = NULL;
    
    if( argc < 2 ) {
        fprintf(stderr, "No file provided\n");
        return 1;
    }
    if(argc == 3 && strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "Input and output file must differ\n");
        return 1;
    }
    if( argc > 3 ) {
        fprintf(stderr, "Too many arguments, usage: reverse <input> <output>\n");
        return 1;
    }
    file = fopen( argv[1], "r" );
    if( file == NULL ) {
        fprintf(stderr, "Unable to open file\n" );
        return 1;
    }
    
    while (!feof(file)) {
        readString(file, &buffer);
        //printf("Read: %s\n", buffer);
        if (strlen(buffer) > 0) {
            insert(&head, buffer);
        }
        free(buffer);
        buffer = NULL;

    }

    fclose(file);



    if(argv[2] != NULL) {
        printf("Printing to file: %s\n", argv[2]);
        traverseList(head, argv[2]);
    } else {
        traverseList(head, NULL);
    }


    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }


    return 0;
}