#include "trabalho_aux_pilha.h"
#include "trabalho_aux_lista.h"
#include<stdio.h>
#include<stdlib.h>

int main(void) {
    printf("-------------------------ITEM 1-------------------------\n");
    const char* expressao1 = "3 2 7 * + 1 -";
    const char* expressao2 = "2 3 4 1 + * -";
    const char* expressao3 = "5 1 2 + 4 * + 3 -";
    const char* expressao4 = "7 5 6 2 / 8 * + 3 + *";
    const char* expressao5 = "2 1 / 4 2 * + 6 5 - 8 2 / + +";

    int resultado1 = calculatePostfix(expressao1);
    int resultado2 = calculatePostfix(expressao2);
    int resultado3 = calculatePostfix(expressao3);
    int resultado4 = calculatePostfix(expressao4);
    int resultado5 = calculatePostfix(expressao5);

    printf("Resultado da expressao "" %s "": %d\n", expressao1, resultado1);
    printf("Resultado da expressao "" %s "": %d\n", expressao2, resultado2);
    printf("Resultado da expressao "" %s "": %d\n", expressao3, resultado3);
    printf("Resultado da expressao "" %s "": %d\n", expressao4, resultado4);
    printf("Resultado da expressao "" %s "": %d\n", expressao5, resultado5);

    printf("-------------------------ITEM 2-------------------------\n");
    NO *list1 = NULL;
    NO *list2 = NULL;

    // Generate two lists of 10 integers in the range [1,100] in ascending order
    for (int i = 1; i <= 10; i++) {
        insertSorted(&list1, rand() % 100 + 1);
        insertSorted(&list2, rand() % 100 + 1);
    }

    printf("lista L1: ");
    printList(list1);

    printf("lista L2: ");
    printList(list2);

    // Create a new list by interleaving the values of the generated lists
    NO *mergedList = interleaveLists(list1,list2);
    printf("lista L3: ");
    printList(mergedList);

    // Free the memory allocated for the lists
    while (list1 != NULL) {
        NO *temp = list1;
        list1 = list1->next;
        free(temp);
    }

    while (list2 != NULL) {
        NO *temp = list2;
        list2 = list2->next;
        free(temp);
    }

    while (mergedList != NULL) {
        NO *temp = mergedList;
        mergedList = mergedList->next;
        free(temp);
    }
    return 0;
}