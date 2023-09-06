#include"trabalho_aux.h"
#include<stdio.h>
#include<stdlib.h>

LinkedList *createEmptyLinkedList(void){
    
}
int checkLinkedEquals(LinkedList *list, int numb){
    while(list->prox != NULL){
        if(list->numb == numb){
            return 0;
        }
        list->prox;
    }
    return 1;
}

LinkedList *CreateMergedLinkedList(LinkedList *list1, LinkedList *list2){


}