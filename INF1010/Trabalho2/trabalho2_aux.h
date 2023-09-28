<<<<<<< HEAD
//structed data 

//struct to player info
struct INFO
{
    int altura;
    int id;
};typedef struct INFO info;

//struct to Binary search tree

struct ABB
{
    info *key;
    struct ABB *father;
    struct ABB *left;
    struct ABB *right;
}; typedef struct ABB abb;

//function prototypes
=======
//structed data

//binary search tree like struct
struct ABB
{
    int info;
    struct ABB *left;
    struct ABB *right;
}; typedef struct ABB abb;

//function prototypes
abb *iniciatetree(void);
abb* insertNode(abb* tree, int value);
void findCompetitors(abb* tree, int heightB, int* visitedNodes);
void printTree(abb* tree);
void freeTree(abb* tree);
>>>>>>> cfb1c8c71d4fc48ab530834ebe4043587636ce26
