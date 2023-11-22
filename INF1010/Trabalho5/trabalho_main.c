#include <stdio.h>
#include <stdlib.h>
#include "trabalho5_aux.h"

int main(void) {
    int V = 11;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 1, 8, 3);
    addEdge(graph, 1, 9, 3);
    addEdge(graph, 1, 10, 1);
    addEdge(graph, 1, 3, 3);
    addEdge(graph, 1, 5, 4);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 2, 10, 1);
    addEdge(graph, 3, 10, 4);
    addEdge(graph, 3, 8, 2);
    addEdge(graph, 3, 4, 1);
    addEdge(graph, 3, 6, 1);
    addEdge(graph, 3, 9, 4);
    addEdge(graph, 4, 7, 2);
    addEdge(graph, 4, 5, 2);
    addEdge(graph, 5, 7, 4);
    addEdge(graph, 5, 8, 1);
    addEdge(graph, 6, 7, 3);
    addEdge(graph, 8, 9, 1);
    addEdge(graph, 8, 10, 2);
    addEdge(graph, 9, 10, 4);

    // Minimum Spanning Tree (MST)
    MST(graph);
    printf("\n");

    // Busca em largura
    int startVertexBFS;
    printf("\nDigite o vértice inicial para busca em largura (BFS): ");
    scanf("%d", &startVertexBFS);
    if (startVertexBFS >= 1 && startVertexBFS <= (V - 1)) {
        BFS(graph, startVertexBFS);
    } else {
        printf("O vértice inicial deve ser um número entre 1 e %d\n", V - 1);
        return 1;
    }

    // Liberar memória
    for (int i = 0; i < V; ++i) {
        struct Node* temp = graph->array[i].head;
        while (temp) {
            struct Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
