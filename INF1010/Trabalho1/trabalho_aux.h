// Definition of node's stack
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Definition of stack
typedef struct Stack {
    Node* top;
} Stack;
int calculatePostfix(const char* expression);