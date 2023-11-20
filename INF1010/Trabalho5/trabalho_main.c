#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó em uma lista de adjacências
struct Node {
    int dest;
    int weight; // Peso da aresta
    struct Node* next;
};

// Estrutura para representar uma lista de adjacências
struct AdjList {
    struct Node *head;
};

// Estrutura para representar um grafo. Um grafo é um array de listas de adjacências.
// O tamanho do array será 'V' (número de vértices no grafo)
struct Graph {
    int V;
    struct AdjList* array;
};

// Função para criar um novo nó de lista de adjacências
struct Node* newAdjListNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Função que cria um grafo de V vértices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Cria um array de listas de adjacências. O tamanho do array será V
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Inicializa cada lista de adjacências como vazia
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adiciona uma aresta ao grafo não direcionado
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Adiciona uma aresta de src a dest. Um novo nó é adicionado à lista de adjacências de src.
    struct Node* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Como o grafo é não direcionado, adiciona uma aresta de dest a src
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Estrutura para representar uma aresta ponderada
struct Edge {
    int src, dest, weight;
};

// Função para encontrar o representante (raiz) de um conjunto usando o algoritmo Union-Find
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;

    // Recursivamente encontra a raiz do conjunto
    return find(parent, parent[i]);
}

// Função para realizar a união (merge) de dois conjuntos usando o algoritmo Union-Find
void unionSets(int parent[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    parent[rootX] = rootY;
}

// Função para comparar as arestas com base nos pesos (usada para ordenar)
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Função para implementar a árvore geradora mínima (MST) usando a estratégia union-find
void MST(struct Graph* graph) {
    int V = graph->V;
    int parent[V]; // Array para armazenar os pais de cada vértice na árvore

    // Inicializa todos os elementos do array parent como -1
    for (int i = 0; i < V; ++i)
        parent[i] = -1;

    // Contar o número total de arestas no grafo
    int numEdges = 0;
    for (int i = 0; i < V; ++i) {
        struct Node* temp = graph->array[i].head;
        while (temp) {
            numEdges++;
            temp = temp->next;
        }
    }

    // Array para armazenar as arestas do grafo
    struct Edge edges[numEdges];

    // Preencher o array de arestas
    int edgeIndex = 0;
    for (int i = 0; i < V; ++i) {
        struct Node* temp = graph->array[i].head;
        while (temp) {
            edges[edgeIndex].src = i;
            edges[edgeIndex].dest = temp->dest;
            edges[edgeIndex].weight = temp->weight; // Utiliza o peso informado
            ++edgeIndex;
            temp = temp->next;
        }
    }

    // Ordenar as arestas com base nos pesos
    qsort(edges, numEdges, sizeof(struct Edge), compareEdges);

    // Array para armazenar as arestas incluídas na MST
    struct Edge mstEdges[V - 1];
    int mstIndex = 0;

    // Construir a MST
    for (int i = 0; i < numEdges && mstIndex < V - 1; ++i) {
        int src = edges[i].src;
        int dest = edges[i].dest;

        int rootSrc = find(parent, src);
        int rootDest = find(parent, dest);

        if (rootSrc != rootDest) {
            // Aresta não forma um ciclo, inclua na MST
            mstEdges[mstIndex] = edges[i];
            ++mstIndex;

            // Realizar a união dos conjuntos
            unionSets(parent, rootSrc, rootDest);
        }
    }

    // Imprimir a MST
    printf("\nÁrvore Geradora Mínima (MST):\n");
    for (int i = 0; i < mstIndex; ++i) {
        printf("(%d, %d) Peso: %d\n", mstEdges[i].src, mstEdges[i].dest, mstEdges[i].weight);
    }
}

// Estrutura para representar uma fila usada pelo BFS
struct queueNode {
    int val;
    struct queueNode* next;
};

// Função para criar um novo nó na fila
struct queueNode* newQueueNode(int v) {
    struct queueNode* temp = (struct queueNode*)malloc(sizeof(struct queueNode));
    temp->val = v;
    temp->next = NULL;
    return temp;
}

// Função para criar uma fila vazia
struct queueNode* createQueue() {
    return NULL;
}

// Função para verificar se a fila está vazia
int isEmpty(struct queueNode* root) {
    return !root;
}

// Função para adicionar um elemento na fila
void enqueue(struct queueNode** root, int val) {
    struct queueNode* temp = newQueueNode(val);

    if (isEmpty(*root))
        *root = temp;
    else {
        struct queueNode* ptr = *root;
        while (ptr->next)
            ptr = ptr->next;
        ptr->next = temp;
    }
}

// Função para remover um elemento da fila
int dequeue(struct queueNode** root) {
    if (isEmpty(*root))
        return -9999;
    struct queueNode* temp = *root;
    *root = (*root)->next;
    int val = temp->val;
    free(temp);

    return val;
}

// Função para implementar a busca em largura (BFS)
void BFS(struct Graph* graph, int startVertex) {
    int v = graph->V;
    int* visited = (int*)malloc(v * sizeof(int));

    for (int i = 0; i < v; i++)
        visited[i] = 0;

    struct queueNode* queue = createQueue();

    visited[startVertex] = 1;
    enqueue(&queue, startVertex);

    printf("\nBusca em largura (BFS) a partir do vértice %d:\n", startVertex);
    while (!isEmpty(queue)) {
        int currentVertex = dequeue(&queue);
        printf("Visitado %d\n", currentVertex);

        struct Node* temp = graph->array[currentVertex].head;
        while (temp) {
            int adjVertex = temp->dest;

            if (visited[adjVertex] == 0) {
                enqueue(&queue, adjVertex);
                visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }

    free(visited);
}

int main() {
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
    if(startVertexBFS>=1 && startVertexBFS<= (V-1)){
        BFS(graph, startVertexBFS);
    }
    else {
        printf("O vértice inicial deve ser um número entre 1 e %d\n", V-1);
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
