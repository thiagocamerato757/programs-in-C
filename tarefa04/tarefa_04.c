//includes
#include <stdio.h>
#include <stdlib.h>

// Symbolic variables
#define MAX_VERTICES 5 

//structured data
struct node 
{
    int vertex;
    struct node* next;
}; 
typedef struct node Node;

struct graph 
{
    Node** linkedList;
}; 
typedef struct graph Graph;

struct edge 
{
    int source;
    int destination;
};
typedef struct edge Edge;

// Function prototypes
Graph* createGraph(int numVertices);
void addEdge(Graph* graph, int source, int destination);
void setGraph(Graph* graph, Edge* edges, int numEdges);
void printGraph(Graph* graph, int numVertices);
int isEdgeRecHelper(Node* currentNode, int destination);
int isEdgeRec(Graph* graph, int source, int destination);
int isEdgeIt(Graph* graph, int source, int destination);
void freeGraph(Graph* graph, int numVertices);

//main function
int main(void) {
    //variables
    int origem;
    int destino;

    Edge edges[] = {
        {0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 1}, {4, 2}
    };
    
    int numVertices = MAX_VERTICES;
    int numEdges = sizeof(edges) / sizeof(edges[0]);
    
    Graph* graph = createGraph(numVertices);
    if(graph == NULL){
        fprintf(stderr,"Erro ao alocar memória do Grafo!\n");
        return 1;
    }

    //execution    
    setGraph(graph, edges, numEdges);
    
     printf("GRAPH:\n");
    printGraph(graph, numVertices);

    printf("TESTE DE ARESTAS !\n");
    origem = 2;
    destino = 0;
    
    printf("Verificando se %d -> %d é uma aresta (versão recursiva): %s\n", origem, destino,
           isEdgeRec(graph, origem, destino) ? "Sim" : "Não");
           
    printf("Verificando se %d -> %d é uma aresta (versão iterativa): %s\n", origem, destino,
           isEdgeIt(graph,origem,destino) ? "Sim" : "Não");

    
    printf("\n");
    origem = 2;
    destino = 4;
    
    printf("Verificando se %d -> %d é uma aresta (versão recursiva): %s\n", origem, destino,
           isEdgeRec(graph, origem, destino) ? "Sim" : "Não");
           
    printf("Verificando se %d -> %d é uma aresta (versão iterativa): %s\n", origem, destino,
           isEdgeIt(graph, origem , destino) ? "Sim" : "Não");
    
    freeGraph(graph, numVertices);
    
    return 0;
}

// Function to create and initialize the graph
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if(graph == NULL){
        return NULL;
    }
    
    graph->linkedList = (Node**)malloc(numVertices * sizeof(Node*));
    if(graph->linkedList == NULL){
        free(graph);
        return NULL;
    }
    
    // Initialize all pointers in the array as NULL
    for (int i = 0; i < numVertices; i++) {
        graph->linkedList[i] = NULL;
    }
    
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int source, int destination) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        return;
    }
    newNode->vertex = destination;
    newNode->next = graph->linkedList[source];
    graph->linkedList[source] = newNode;
}

// Function to construct the graph
void setGraph(Graph* graph, Edge* edges, int numEdges) {
    for (int i = 0; i < numEdges; i++) {
        int source = edges[i].source;
        int destination = edges[i].destination;
        
        addEdge(graph, source, destination);
    }
}

// Function to print the graph
void printGraph(Graph* graph, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        Node* currentNode = graph->linkedList[i];
        
        while (currentNode != NULL) {
            printf("(%d -> %d) ", i, currentNode->vertex);
            currentNode = currentNode->next;
        }
        
    }
    printf("\n\n");
}

// Recursive helper function to check if two vertices form an edge in the graph
int isEdgeRecHelper(Node* currentNode, int destination) {
    if (currentNode == NULL) {
        return 0;
    }
    
    else if (currentNode->vertex == destination) {
        return 1;
    }
    
    return isEdgeRecHelper(currentNode->next, destination);
}

// Recursive function to check if two vertices form an edge in the graph
int isEdgeRec(Graph* graph, int source, int destination) {
    Node* currentNode = graph->linkedList[source];
    return isEdgeRecHelper(currentNode, destination);
}

// Iterative function to check if two vertices form an edge in the graph
int isEdgeIt(Graph* graph, int source, int destination) {
    Node* currentNode = graph->linkedList[source];
    
    while (currentNode != NULL) {
        if (currentNode->vertex == destination) {
            return 1;
        }
        
        currentNode = currentNode->next;
    }
    
    return 0;
}

// Function to free the memory allocated for the graph
void freeGraph(Graph* graph, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        Node* currentNode = graph->linkedList[i];
        
        while (currentNode != NULL) {
            Node* temp = currentNode;
            currentNode = currentNode->next;
            free(temp);
        }
    }
    
    free(graph->linkedList);
    free(graph);
    printf(">>> Grafo liberado com sucesso !\n");
}