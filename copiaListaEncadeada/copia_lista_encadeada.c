//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structed data
typedef struct no {
    int ident;
    char nome[20];
    char sexo;
    struct no* prox;
} No;

//function prototypes
No* fazCopiaRecursiva(No* original);
void imprimirLista(No* lista);

//main function
int main(void) {
    //variables
    No* no1;
    No* no2;
    No* no3;
    No* novaLista;
    No* atual;

    //execution
    no1 = (No*)malloc(sizeof(No));
    no2 = (No*)malloc(sizeof(No));
    no3 = (No*)malloc(sizeof(No));
    if(no1 == NULL || no2 == NULL || no3 == NULL){
        fprintf(stderr,"Error allocating node's memory !\n");
        exit(1);
    }

    no1->ident = 1;
    strcpy(no1->nome, "João");
    no1->sexo = 'H';
    no1->prox = no2;

    no2->ident = 2;
    strcpy(no2->nome, "Maria");
    no2->sexo = 'M';
    no2->prox = no3;

    no3->ident = 3;
    strcpy(no3->nome, "Pedro");
    no3->sexo = 'H';
    no3->prox = NULL;

    // Copiando a lista original
    novaLista = fazCopiaRecursiva(no1);
    if(novaLista == NULL){
        fprintf(stderr,"Error allocatibg list's memory !\n");
        exit(1);
    }

    printf("Nova lista: ");
    imprimirLista(novaLista);

    //deallocating dynamic allocated memory
    atual = novaLista;
    while (atual != NULL) {
        No* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    return 0;
}
//recursive function to copy info of a node into a new list
No* fazCopiaRecursiva(No* original) {
    if (original == NULL) {
        return NULL;
    }

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        return NULL;
    }

    novoNo->ident = original->ident;
    strcpy(novoNo->nome, original->nome);
    novoNo->sexo = original->sexo;

    novoNo->prox = fazCopiaRecursiva(original->prox);

    return novoNo;
}

//function to print linked list
void imprimirLista(No* lista) {
    No* atual = lista;
    while (atual != NULL) {
        printf("[%d, \"%s\", %c] -> ", atual->ident, atual->nome, atual->sexo);
        atual = atual->prox;
    }
    printf("NULL\n");
}
