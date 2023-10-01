#include<stdio.h>
#include<stdlib.h>
#include "AUX_arvore_binaria_busca.h"

int main(void) {
    BinarySearchTree *arv;

    arv->inf.numb = 15;
    // Inserindo os elementos na árvore
    addTree(arv,3);
    addTree(arv,7);
    addTree(arv,17);
    addTree(arv,29);
    inorder(arv);

    // Removendo os elementos da árvore
    arv = deleteBinaryTree(arv, 5);
    arv = deleteBinaryTree(arv, 15);
    arv = deleteBinaryTree(arv, 16);
    arv = deleteBinaryTree(arv, 18);
    arv = deleteBinaryTree(arv, 22);

    printf("Arvore resultante em ordem: ");
    inorder(arv);
    printf("\n");

    if (isBalanced(arv)) {
        printf("A arvore esta balanceada.\n");
    } else {
        printf("A arvore nao esta balanceada.\n");
    }

    return 0;
}