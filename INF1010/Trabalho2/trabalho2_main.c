#include "trabalho2_aux.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    abb* root;
    int visitedNodes = 0;
    int heightB;
    int heights[] = {120, 112, 137, 95, 115, 125, 150, 107, 118};
    int numCompetitors = sizeof(heights) / sizeof(heights[0]);

    root = iniciatetree();
    for (int i = 0; i < numCompetitors; i++) {
        root = insertNode(root, heights[i]);
    }

    printf("Alturas dos competidores em ordem:\n");
    printTree(root);
    printf("\n\n");
    printf("Digite a altura do competidor B:\n");
    scanf("%d",&heightB);
    findCompetitors(root, heightB, &visitedNodes);
    printf("\nNumero de nos visitados: %d\n", visitedNodes);
    freeTree(root);

    return 0;
}
