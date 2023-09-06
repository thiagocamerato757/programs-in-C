//structed data 

// Definition of node's stack
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Definition of stack
typedef struct Stack {
    Node* top;
} Stack;

//Definition of a linked list of integers
typedef struct LinkedList {
    int numb;
    struct LinkedList *prox;
} LinkedList;

//function prototypes

int calculatePostfix(const char* expression);