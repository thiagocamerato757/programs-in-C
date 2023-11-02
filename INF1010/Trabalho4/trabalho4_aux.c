#include <stdio.h>
#include <stdlib.h>
#include"trabalho4_aux.h"

t_no *cria_no(void) {
    t_no *novo = (t_no *)malloc(sizeof(t_no));
    novo->ndesc = 0;
    for (int i = 0; i <= MAX; i++) {
        novo->ramo[i] = NULL;
    }
    return novo;
}

void imprime_intervalo(t_no *arv, int lim_inf, int lim_sup) {
    if (arv) {
        int i;
        for (i = 0; i < arv->ndesc; i++) {
            if (arv->chave[i] > lim_inf) {
                imprime_intervalo(arv->ramo[i], lim_inf, lim_sup);
            }

            if (arv->chave[i] > lim_inf && arv->chave[i] < lim_sup) {
                printf("%d ", arv->chave[i]);
            }

            if (arv->chave[i] < lim_sup) {
                imprime_intervalo(arv->ramo[i + 1], lim_inf, lim_sup);
            }
        }
    }
}

t_no *insere_chave(t_no *raiz, int chave) {
    if (!raiz) {
        raiz = cria_no();
        raiz->chave[0] = chave;
        raiz->ndesc = 1;
        return raiz;
    } else {
        if (raiz->ndesc < MAX) {
            int i = raiz->ndesc - 1;
            while (i >= 0 && chave < raiz->chave[i]) {
                raiz->chave[i + 1] = raiz->chave[i];
                i--;
            }
            raiz->chave[i + 1] = chave;
            raiz->ndesc++;
        } else {
            int i = 0;
            while (i < raiz->ndesc && chave > raiz->chave[i]) {
                i++;
            }
            raiz->ramo[i] = insere_chave(raiz->ramo[i], chave);
        }

        if (raiz->ndesc > MAX) {
            int meio = raiz->ndesc / 2;
            t_no *novo = cria_no();
            for (int j = 0; j < MAX - meio; j++) {
                novo->chave[j] = raiz->chave[j + meio];
                novo->ramo[j] = raiz->ramo[j + meio];
            }
            novo->ramo[MAX - meio] = raiz->ramo[MAX];
            raiz->ndesc = meio;
            novo->ndesc = MAX - meio;
            return novo;
        }
    }
    return raiz;
}

void imprime_simetrica(t_no *raiz) {
    if (raiz) {
        for (int i = 0; i < raiz->ndesc; i++) {
            imprime_simetrica(raiz->ramo[i]);
            printf("%d ", raiz->chave[i]);
        }
        imprime_simetrica(raiz->ramo[raiz->ndesc]);
    }
}
