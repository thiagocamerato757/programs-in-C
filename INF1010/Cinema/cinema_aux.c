#include <stdio.h>
#include <stdlib.h>
#include "cinema_aux.h"

fila *criaFila(void){
    fila *fl;
    fl = (fila*)malloc(sizeof(fila));
    if (!fl) return NULL;
    
    fl->inicio = NULL;
    fl->fim = NULL;
    return fl;
}

void adiciona(fila *fl, int info1, int info2){
    pessoa *ps = (pessoa*)malloc(sizeof(pessoa));
    if (!ps) return;

    ps->id = info1;
    ps->idade = info2;
    ps->prox = NULL;

    if (fl->fim != NULL){
        fl->fim->prox = ps;
    }
    else{ 
        fl->inicio = ps;
    }
    fl->fim = ps;
}

void imprimePassagem(fila *fl1, fila *fl2){
    pessoa *pessoaA = fl1->inicio;
    pessoa *pessoaB = fl2->inicio;

    while (pessoaA || pessoaB){
        if (pessoaA && pessoaB){
            if (pessoaA->idade > pessoaB->idade || (pessoaA->idade == pessoaB->idade && pessoaA == fl1->inicio)){
                printf("Pessoa de idade %d passou\n", pessoaA->idade);
                pessoaA = pessoaA->prox;
            }
            else{
                printf("Pessoa de idade %d passou\n", pessoaB->idade);
                pessoaB = pessoaB->prox;
            }
        }
        else if (pessoaA){
            printf("Pessoa de idade %d passou\n", pessoaA->idade);
            pessoaA = pessoaA->prox;
        }
        else if (pessoaB){
            printf("Pessoa de idade %d passou\n", pessoaB->idade);
            pessoaB = pessoaB->prox;
        }
    }
}
