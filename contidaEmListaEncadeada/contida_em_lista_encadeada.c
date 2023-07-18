//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structed data
typedef struct noLista NoLista;
struct noLista {
    int codigo;
    char nome[51];
    NoLista* prox;
};

//function prototypes
int testaContida(NoLista* list1, NoLista* list2);

//main function
int main(void) {
    //variables
    NoLista* lista1;
    NoLista* lista2;
    NoLista* lista3;
    int contido;
    NoLista* temp;
    NoLista* atual1;
    NoLista* atual2;
    NoLista* atual3;

    //execution 
    lista1 = (NoLista*)malloc(sizeof(NoLista));
    if (lista1 == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    lista1->codigo = 888;
    strcpy(lista1->nome, "lia");
    lista1->prox = NULL;

    lista1->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista1->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista1);
        exit(1);
    }
    lista1->prox->codigo = 222;
    strcpy(lista1->prox->nome, "leo");
    lista1->prox->prox = NULL;

    lista1->prox->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista1->prox->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista1->prox);
        free(lista1);
        exit(1);
    }
    lista1->prox->prox->codigo = 777;
    strcpy(lista1->prox->prox->nome, "rosa");
    lista1->prox->prox->prox = NULL;

    lista1->prox->prox->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista1->prox->prox->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista1->prox->prox);
        free(lista1->prox);
        free(lista1);
        exit(1);
    }
    lista1->prox->prox->prox->codigo = 333;
    strcpy(lista1->prox->prox->prox->nome, "rui");
    lista1->prox->prox->prox->prox = NULL;

    lista2 = (NoLista*)malloc(sizeof(NoLista));
    if (lista2 == NULL) {
        printf("Memory allocation failed.\n");
        free(lista1->prox->prox->prox->prox);
        free(lista1->prox->prox->prox);
        free(lista1->prox->prox);
        free(lista1->prox);
        free(lista1);
        exit(1);
    }
    lista2->codigo = 111;
    strcpy(lista2->nome, "edu");
    lista2->prox = NULL;

    lista2->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista2->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista2);
        free(lista1->prox->prox->prox->prox);
        free(lista1->prox->prox->prox);
        free(lista1->prox->prox);
        free(lista1->prox);
        free(lista1);
        exit(1);
    }
    lista2->prox->codigo = 222;
    strcpy(lista2->prox->nome, "leo");
    lista2->prox->prox = NULL;

    lista2->prox->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista2->prox->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista2->prox);
        free(lista2);
        free(lista1->prox->prox->prox->prox);
        free(lista1->prox->prox->prox);
        free(lista1->prox->prox);
        free(lista1->prox);
        free(lista1);
        exit(1);
    }
    lista2->prox->prox->codigo = 333;
    strcpy(lista2->prox->prox->nome, "rui");
    lista2->prox->prox->prox = NULL;

    lista2->prox->prox->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista2->prox->prox->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista2->prox->prox);
        free(lista2->prox);
        free(lista2);
        free(lista1->prox->prox->prox->prox);
        free(lista1->prox->prox->prox);
        free(lista1->prox->prox);
        free(lista1->prox);
        free(lista1);
        exit(1);
    }
    lista2->prox->prox->prox->codigo = 446;
    strcpy(lista2->prox->prox->prox->nome, "cris");
    lista2->prox->prox->prox->prox = NULL;

    lista2->prox->prox->prox->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista2->prox->prox->prox->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista2->prox->prox->prox);
        free(lista2->prox->prox);
        free(lista2->prox);
        free(lista2);
        free(lista1->prox->prox->prox->prox);
        free(lista1->prox->prox->prox);
        free(lista1->prox->prox);
        free(lista1->prox);
        free(lista1);
        exit(1);
    }
    lista2->prox->prox->prox->prox->codigo = 666;
    strcpy(lista2->prox->prox->prox->prox->nome, "cadu");
    lista2->prox->prox->prox->prox->prox = NULL;

    lista2->prox->prox->prox->prox->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista2->prox->prox->prox->prox->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista2->prox->prox->prox->prox);
        free(lista2->prox->prox->prox);
        free(lista2->prox->prox);
        free(lista2->prox);
        free(lista2);
        free(lista1->prox->prox->prox->prox);
        free(lista1->prox->prox->prox);
        free(lista1->prox->prox);
        free(lista1->prox);
        free(lista1);
        exit(1);
    }
    lista2->prox->prox->prox->prox->prox->codigo = 777;
    strcpy(lista2->prox->prox->prox->prox->prox->nome, "rosa");
    lista2->prox->prox->prox->prox->prox->prox = NULL;

    lista2->prox->prox->prox->prox->prox->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista2->prox->prox->prox->prox->prox->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista2->prox->prox->prox->prox->prox);
        free(lista2->prox->prox->prox->prox);
        free(lista2->prox->prox->prox);
        free(lista2->prox->prox);
        free(lista2->prox);
        free(lista2);
        free(lista1->prox->prox->prox->prox);
        free(lista1->prox->prox->prox);
        free(lista1->prox->prox);
        free(lista1->prox);
        free(lista1);
        exit(1);
    }
    lista2->prox->prox->prox->prox->prox->prox->codigo = 888;
    strcpy(lista2->prox->prox->prox->prox->prox->prox->nome, "lia");
    lista2->prox->prox->prox->prox->prox->prox->prox = NULL;

    
    lista3 = (NoLista*)malloc(sizeof(NoLista));
    if (lista3 == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    lista3->codigo = 554;
    strcpy(lista3->nome, "vera");
    lista3->prox = NULL;

    lista3->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista3->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista3);
        exit(1);
    }
    lista3->prox->codigo = 777;
    strcpy(lista3->prox->nome, "rosa");
    lista3->prox->prox = NULL;

    lista3->prox->prox = (NoLista*)malloc(sizeof(NoLista));
    if (lista3->prox->prox == NULL) {
        printf("Memory allocation failed.\n");
        free(lista3->prox);
        free(lista3);
        exit(1);
    }
    lista3->prox->prox->codigo = 333;
    strcpy(lista3->prox->prox->nome, "rui");
    lista3->prox->prox->prox = NULL;

    printf("Lista 1: ");
    atual1 = lista1;
    while (atual1 != NULL) {
        printf("(%d, %s) -> ", atual1->codigo, atual1->nome);
        atual1 = atual1->prox;
    }
    printf("NULL\n");

    printf("Lista 2: ");
    atual2 = lista2;
    while (atual2 != NULL) {
        printf("(%d, %s) -> ", atual2->codigo, atual2->nome);
        atual2 = atual2->prox;
    }
    printf("NULL\n");

    printf("Lista 3: ");
    atual3 = lista3;
    while (atual3 != NULL) {
        printf("(%d, %s) -> ", atual3->codigo, atual3->nome);
        atual3 = atual3->prox;
    }
    printf("NULL\n\n");

    contido = testaContida(lista1, lista2);
    printf("Lista 1 está contida em Lista 2? %s\n\n", contido ? "Sim" : "Não");

    contido = testaContida(lista3, lista2);
    printf("Lista 3 está contida em Lista 2? %s\n\n", contido ? "Sim" : "Não");

    //deallocating dynamic allocated memory 
    atual1 = lista1;
    while (atual1 != NULL) {
        temp = atual1;
        atual1 = atual1->prox;
        free(temp);
    }

    atual2 = lista2;
    while (atual2 != NULL) {
        temp = atual2;
        atual2 = atual2->prox;
        free(temp);
    }

    atual3 = lista3;
    while (atual3 != NULL) {
        temp = atual3;
        atual3 = atual3->prox;
        free(temp);
    }

    return 0;
}

//function to check if all linked list's terms(codes) are in another linked list 
int testaContida(NoLista* list1, NoLista* list2) {
    NoLista* current1 = list1;
    NoLista* current2 = list2;

    while (current1 != NULL) {
        int encontrado = 0;
        current2 = list2;

        while (current2 != NULL) {
            if (current1->codigo == current2->codigo) {
                encontrado = 1;
                break;
            }

            current2 = current2->prox;
        }

        if (!encontrado) {
            return 0;
        }

        current1 = current1->prox;
    }

    return 1;
}
