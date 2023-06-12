//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structed data
typedef struct Informacao {
    int codigo;
    char nome[31];
} Informacao;

typedef struct No {
    Informacao *info;
    struct No *prox;
} No;

//function prototypes
No* insereElemento(No* lista, int codigo, char* nome);
No* quebraAoMeio(No* lista);

//main function
int main(void) {
    //variables
    No* lista = NULL;
    No* segundaMetade;

    lista = insereElemento(lista, 1, "Elemento 1");
    lista = insereElemento(lista, 2, "Elemento 2");
    lista = insereElemento(lista, 3, "Elemento 3");
    lista = insereElemento(lista, 4, "Elemento 4");
    lista = insereElemento(lista, 5, "Elemento 5");

    segundaMetade = quebraAoMeio(lista);

    printf("Primeira metade:\n");
    No* current = lista;
    while (current != NULL) {
        printf("Código: %d, Nome: %s\n", current->info->codigo, current->info->nome);
        current = current->prox;
    }

    printf("\nSegunda metade:\n");
    current = segundaMetade;
    while (current != NULL) {
        printf("Código: %d, Nome: %s\n", current->info->codigo, current->info->nome);
        current = current->prox;
    }

    //dealocating dynamic allocated memory
    current = lista;
    while (current != NULL) {
        No* next = current->prox;
        free(current->info);
        free(current);
        current = next;
    }

    current = segundaMetade;
    while (current != NULL) {
        No* next = current->prox;
        free(current->info);
        free(current);
        current = next;
    }
    printf("memórias liberadas !\n");
    return 0;
}

//function to insert an element in the linked list
No* insereElemento(No* lista, int codigo, char* nome) {
    //creating a new node
    No* novoNo = malloc(sizeof(No));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro: falha na alocação de memória.\n");
        exit(1);
    }

    Informacao* novaInfo = malloc(sizeof(Informacao));
    if (novaInfo == NULL) {
        fprintf(stderr, "Erro: falha na alocação de memória.\n");
        exit(1);
    }
    novaInfo->codigo = codigo;
    strncpy(novaInfo->nome, nome, 31);

    novoNo->info = novaInfo;
    novoNo->prox = NULL;

    if (lista == NULL) {
        return novoNo;
    }

    No* current = lista;
    while (current->prox != NULL) {
        current = current->prox;
    }

    current->prox = novoNo;

    return lista;
}

//function that divides a linked list by two
No* quebraAoMeio(No* lista) {
    if (lista == NULL || lista->prox == NULL)
        return NULL; // Returns NULL in case the number is lesser than 2

    No* slow = lista;
    No* fast = lista->prox;

    while (fast != NULL) {
        fast = fast->prox;

        if (fast != NULL) {
            slow = slow->prox;
            fast = fast->prox;
        }
    }

    No* segundaMetade = slow->prox;
    slow->prox = NULL;

    return segundaMetade;
}