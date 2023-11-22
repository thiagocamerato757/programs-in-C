#include <stdio.h>
#include <stdlib.h>
#include"trabalho4_aux.h"

int main(void) {
    t_no *arvore = NULL;
    int chaves[] = {10, 40, 50, 60, 70, 75, 80, 90, 100, 110, 115, 120, 130, 135, 140, 170, 200, 220, 230, 240, 250};
    int num_chaves = sizeof(chaves) / sizeof(chaves[0]);

    for (int i = 0; i < num_chaves; i++) {
        arvore = insere_chave(arvore, chaves[i]);
        printf("inserção de %03d: ", chaves[i]);
        imprime_simetrica(arvore);
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------------------------------------\n");
    int lim_inf[] = {25, 80, 120, 70, 200};
    int lim_sup[] = {75, 110, 140, 60, 230};

    for (int i = 0; i < 5; i++) {
        printf("Chaves no intervalo (%d, %d): ", lim_inf[i], lim_sup[i]);
        imprime_intervalo(arvore, lim_inf[i], lim_sup[i]);
        printf("\n");
    }

    return 0;
}
