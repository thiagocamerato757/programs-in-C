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

struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest, int weight);
void MST(struct Graph* graph);
void BFS(struct Graph* graph, int startVertex);

