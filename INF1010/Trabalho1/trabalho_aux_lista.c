#include <stdio.h>
#include <stdlib.h>
#include "trabalho_aux_lista.h"

// Function to create a new nO
NO *createNO(int value) {
    NO *newNO = (NO *)malloc(sizeof(NO));
    if (newNO == NULL) {
        fprintf(stderr,"Memory allocation error");
        exit(1);
    }
    newNO->value = value;
    newNO->next = NULL;
    return newNO;
}

// Function to insert a nO into the list in sorted order
void insertSorted(NO **head, int value) {
    NO *newNO = createNO(value);

    if (*head == NULL || value < (*head)->value) {
        newNO->next = *head;
        *head = newNO;
        return;
    }

    NO *current = *head;
    while (current->next != NULL && current->next->value < value) {
        current = current->next;
    }

    newNO->next = current->next;
    current->next = newNO;
}

// Function to create a new list by interleaving values from two lists
NO *interleaveLists(NO *list1, NO *list2) {
    NO *result = NULL; // Initialize the result list
    int lastInsertedValue = -1; // Initialize with a value that is not in the lists

    while (list1 != NULL || list2 != NULL) {
        int valueToInsert;

        // Determine which value to insert based on the smaller of the two lists
        if (list1 == NULL || (list2 != NULL && list2->value < list1->value)) {
            valueToInsert = list2->value;
            list2 = list2->next;
        } else {
            valueToInsert = list1->value;
            list1 = list1->next;
        }

        // Check for duplicates before inserting
        if (valueToInsert != lastInsertedValue) {
            insertSorted(&result, valueToInsert);
            lastInsertedValue = valueToInsert;
        }
    }

    return result;
}

// Function to print the elements of the list
void printList(NO *head) {
    NO *current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}
