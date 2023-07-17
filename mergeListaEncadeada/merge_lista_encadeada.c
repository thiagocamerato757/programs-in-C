//includes
#include <stdio.h>
#include <stdlib.h>

//structed data
typedef struct Node {
    int codigo;
    char* nome;
    struct Node* prox;
} Node;

//function prototypes
Node* criarNo(int codigo, char* nome);
Node* MergeListas(Node* lista1, Node* lista2);
void imprimirLista(Node* lista);
void imprimirLista(Node* lista);
void liberarLista(Node* lista);

//main function
int main(void) {
    //variables
    Node* lista1;
    Node* lista2;
    Node* listaResultante;
    
    //execution

    lista1 = criarNo(111, "leo");
    lista1->prox = criarNo(333, "rui");
    lista1->prox->prox = criarNo(446, "cris");
    lista1->prox->prox->prox = criarNo(558, "lara");
    lista1->prox->prox->prox->prox = criarNo(666, "cadu");
    lista1->prox->prox->prox->prox->prox = criarNo(777, "rosa");
    lista1->prox->prox->prox->prox->prox->prox = criarNo(999, "bia");

    lista2 = criarNo(111, "leo");
    lista2->prox = criarNo(333, "rui");
    lista2->prox->prox = criarNo(440, "edu");
    lista2->prox->prox->prox = criarNo(554, "vera");
    lista2->prox->prox->prox->prox = criarNo(777, "rosa");
    lista2->prox->prox->prox->prox->prox = criarNo(888, "lia");

    //merging two linked lists
    listaResultante = MergeListas(lista1, lista2);

    imprimirLista(listaResultante);

    //deallocating dynamic allocated memory
    liberarLista(listaResultante);

    return 0;
}

//function to create a new node
Node* criarNo(int codigo, char* nome) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo nó.\n");
        exit(1);
    }
    novoNo->codigo = codigo;
    novoNo->nome = nome;
    novoNo->prox = NULL;
    return novoNo;
}

//function to insert a node into the merged list 
void inserirNo(Node** listaResultante, Node* novoNo) {
    if (*listaResultante == NULL) {
        *listaResultante = novoNo;
    } 
    else {
        Node* atual = *listaResultante;
        Node* anterior = NULL;
        while (atual != NULL && atual->codigo < novoNo->codigo) {
            anterior = atual;
            atual = atual->prox;
        }
        if (atual != NULL && atual->codigo == novoNo->codigo) {
            free(novoNo); // Descarta nós com códigos repetidos
        } 
        else {
            if (anterior == NULL) {
                novoNo->prox = *listaResultante;
                *listaResultante = novoNo;
            } 
            else {
                anterior->prox = novoNo;
                novoNo->prox = atual;
            }
        }
    }
}

//function to merge two ordenated linked lists 
Node* MergeListas(Node* lista1, Node* lista2) {
    Node* listaResultante = NULL;

    while (lista1 != NULL && lista2 != NULL) {
        if (lista1->codigo < lista2->codigo) {
            inserirNo(&listaResultante, criarNo(lista1->codigo, lista1->nome));
            lista1 = lista1->prox;
        } 
        else if (lista1->codigo > lista2->codigo) {
            inserirNo(&listaResultante, criarNo(lista2->codigo, lista2->nome));
            lista2 = lista2->prox;
        } 
        else {
            // Códigos iguais, escolher um dos nós
            inserirNo(&listaResultante, criarNo(lista1->codigo, lista1->nome));
            lista1 = lista1->prox;
            lista2 = lista2->prox;
        }
    }

    while (lista1 != NULL) {
        inserirNo(&listaResultante, criarNo(lista1->codigo, lista1->nome));
        lista1 = lista1->prox;
    }

    while (lista2 != NULL) {
        inserirNo(&listaResultante, criarNo(lista2->codigo, lista2->nome));
        lista2 = lista2->prox;
    }

    return listaResultante;
}

//function to print a linked list 
void imprimirLista(Node* lista) {
    Node* atual = lista;
    while (atual != NULL) {
        printf("[%d, \"%s\"] ", atual->codigo, atual->nome);
        atual = atual->prox;
    }
    printf("\n");
}

//function to free all the dynamic allocated memory
void liberarLista(Node* lista) {
    Node* atual = lista;
    while (atual != NULL) {
        Node* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}