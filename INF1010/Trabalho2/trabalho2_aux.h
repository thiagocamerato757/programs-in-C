
//structed data 

//struct to Binary search tree

struct ABB
{
    int info;
    struct ABB *father;
    struct ABB *left;
    struct ABB *right;
}; typedef struct ABB abb;

//function prototypes
abb *iniciatetree(void);
abb* insertNode(abb* tree, int value);
void findCompetitors(abb* tree, int heightB, int* visitedNodes);
void printTree(abb* tree);
void freeTree(abb* tree);
