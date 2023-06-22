//includes 
#include <stdio.h>
#include <stdlib.h>

//structed data
struct retangulo {
    float comprimento;
    float largura;
};
typedef struct retangulo Retangulo;

struct no {
    Retangulo *ret;
    struct no *prox;
};
typedef struct no No;

//function prototypes
No* insere(No *LinkedList, float med1, float med2);
void imprimeRec(No *linkedList);
float areaTotalRec(No *linkedList);
void liberaRec(No *linkedList);

//main function
int main(void) {
    //variables
    int qtdTerrenos;
    float medida1;
    float medida2;
    No *lista = NULL;
    float areaTotal;

    //execution
    printf("Digite a quantidade de terrenos:\n");
    scanf("%d", &qtdTerrenos);

    for (int i = 0; i < qtdTerrenos; i++) {
        printf("Digite o comprimento (em metros) do terreno %d:\n", i + 1);
        scanf("%f", &medida1);
        printf("Digite a largura (em metros) do terreno %d:\n", i + 1);
        scanf("%f", &medida2);

        lista = insere(lista, medida1, medida2);
        if (lista == NULL) {
            fprintf(stderr, "Erro ao alocar novo nó\n");
            exit(1);
        }
    }

    printf("TERRENOS:\n");
    imprimeRec(lista);
    areaTotal = areaTotalRec(lista);
    printf("\nÁrea total comprada: %.2f m^2\n", areaTotal);

    liberaRec(lista);
    printf("Memórias liberadas com sucesso!\n");

    return 0;
}

No* insere(No *LinkedList, float med1, float med2) {
    No *newNode = (No *)malloc(sizeof(No));
    newNode->ret = (Retangulo *)malloc(sizeof(Retangulo));
    if (newNode == NULL || newNode->ret == NULL) {
        return NULL;
    }

    newNode->ret->comprimento = med1;
    newNode->ret->largura = med2;
    newNode->prox = LinkedList;

    return newNode;
}

void imprimeRec(No *linkedList) {
    if (linkedList != NULL) {
        printf("[%.1fm X %.1fm] ", linkedList->ret->comprimento, linkedList->ret->largura);
        imprimeRec(linkedList->prox);
    }
}

float areaTotalRec(No *linkedList) {
    if (linkedList == NULL) {
        return 0.0;
    }
    return (linkedList->ret->comprimento * linkedList->ret->largura) + areaTotalRec(linkedList->prox);
}

void liberaRec(No *linkedList) {
    if (linkedList == NULL) {
    liberaRec(linkedList->prox);
    free(linkedList->ret);
    free(linkedList);
    }
   
}
