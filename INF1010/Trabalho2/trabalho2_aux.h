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