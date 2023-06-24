//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structed data
struct pedido 
{
    int matricula;
    char tipoDoPedido[21];
    struct pedido *prox;
};
typedef struct pedido Pedido;

//function prototypes
int maiorMatriculaRec(Pedido *lista);
int maiorMatriculaIt(Pedido *lista);

//main function
int main(void) {
    //variables
    Pedido *lista = NULL;
    Pedido *novoPedido;
    char tipo[21];
    int matricula;
    int maiorRec;
    int maiorIt;

    //execution
    printf("Digite os pedidos de bolsa (digite -1 para encerrar):\n");

    while (1) {
        printf("Matrícula: ");
        scanf("%d", &matricula);

        if (matricula == -1) {
            break;
        }

        printf("Tipo do pedido (soc/ic/mest/dout): ");
        scanf("%s", tipo);

        novoPedido = (Pedido *)malloc(sizeof(Pedido));
        novoPedido->matricula = matricula;
        strcpy(novoPedido->tipoDoPedido, tipo);
        novoPedido->prox = NULL;

        
        if (lista == NULL) {
            lista = novoPedido;
        } else {
            novoPedido->prox = lista;
            lista = novoPedido;
        }
    }

   
    maiorRec = maiorMatriculaRec(lista);

    if (maiorRec == -1) {
        printf("Nenhum pedido de bolsa encontrado.\n");
    } 
    else {
        printf("Maior matrícula: %d\n", maiorRec);
    }
    maiorIt = maiorMatriculaIt(lista);

    if (maiorIt == -1) {
        printf("Nenhum pedido de bolsa encontrado.\n");
    } 
    
    else {
        printf("Maior matrícula: %d\n", maiorIt);
    }

    //deallocating dinamyc allocated memory
    Pedido *temp;

    while (lista != NULL) {
        temp = lista;
        lista = lista->prox;
        free(temp);
    }

    return 0;
}

//recursive function to find the greater integer 
int maiorMatriculaRec(Pedido *lista) {
    if (lista == NULL) {
        return -1;
    }

    if (lista->prox == NULL) {
        return lista->matricula;
    }

    int proximaMatricula = maiorMatriculaRec(lista->prox);

    return (lista->matricula > proximaMatricula) ? lista->matricula : proximaMatricula;
}
//iterative function to find the greater integer 
int maiorMatriculaIt(Pedido *lista) {
    if (lista == NULL) {
        return -1;
    }

    int maior = lista->matricula;

    while (lista != NULL) {
        if (lista->matricula > maior) {
            maior = lista->matricula;
        }
        lista = lista->prox;
    }

    return maior;
}

