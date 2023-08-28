#include"cinema_aux.h"
#include<stdio.h>

int main(void) {
    fila *filaA = criaFila();
    fila *filaB = criaFila();

    // Adicionar pessoas às filas (use suas próprias informações)
    adiciona(filaA, 1, 30);
    adiciona(filaA, 2, 25);
    adiciona(filaA, 3, 35);

    adiciona(filaB, 4, 28);
    adiciona(filaB, 5, 30);
    adiciona(filaB, 6, 27);

    imprimePassagem(filaA, filaB);

    return 0;
}