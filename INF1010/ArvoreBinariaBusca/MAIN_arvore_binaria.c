#include<stdio.h>
#include<stdlib.h>
#include "AUX_arvore_binaria_busca.h"

int main(void) {
    BinarySearchTree *arv = createTree();
    
    // Inserindo os elementos na árvore
    addTree(arv,15);
    addTree(arv,10);
    addTree(arv,20);
    addTree(arv,5);
    addTree(arv,18);
    addTree(arv,16);
    addTree(arv,19);
    addTree(arv,25);
    addTree(arv,22);
    addTree(arv,30);
    addTree(arv,21);
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