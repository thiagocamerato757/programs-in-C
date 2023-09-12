//structed data


//struct to represent a value 
struct Info
{
    int numb;
};typedef struct Info info;

//struct to represent a Binary search tree 
struct BinarySearchTree
{
    info inf;
    struct BinarySearchTree * left;
    struct BinarySearchTree * right;

};typedef struct BinarySearchTree BinarySearchTree;

//function prototypes
BinarySearchTree *createTree(void);
void addTree(BinarySearchTree *tree, int n);
int isBalanced(BinarySearchTree *tree);
BinarySearchTree *deleteBinaryTree(BinarySearchTree *tree, int inf);
void inorder(BinarySearchTree *tree);