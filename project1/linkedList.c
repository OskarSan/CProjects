/*
    AI USE STATEMENT
    Oskar Sankila
    000471121

    Github Copilot was used for fixing and verifying 
    the syntax in the code, 
    as well as explaining some of the used functions end their parameters.

    Other AI tools were not used.

*/





#include <stdio.h>



struct Node {
    int data;
    struct Node* next;
};



struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}


void traverseList(struct Node* head, char* file) {
    
    struct Node* temp = head;

    if (file != NULL) {
        FILE *output = fopen(file, "w");
        while (temp != NULL) {
            fprintf(output, "%d\n", temp->data);
            temp = temp->next;
        }
        fclose(output);
        return;
    }
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

}
