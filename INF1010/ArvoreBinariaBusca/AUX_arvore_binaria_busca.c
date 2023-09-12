#include"AUX_arvore_binaria_busca.h"
#include<stdio.h>
#include<stdlib.h>

BinarySearchTree *createTree(void){
    return NULL;
}

void addTree(BinarySearchTree *tree, int n){
    BinarySearchTree *new;
    new = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    if(!new) return;
    new->inf.numb = n;
    new->left = NULL;
    new->right = NULL;

    if(!(tree)){
        tree = new;
        return;
    }

    BinarySearchTree *current = tree;
    BinarySearchTree *parent = NULL;
    while(current != NULL){
        parent = current;
        if(current->inf.numb > new->inf.numb){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }

    if(parent->inf.numb > new->inf.numb){
        parent->left = new;
    }
    else{
        parent->right = new;
    }
    return;
}

int getHeight(BinarySearchTree *tree) {
    if (tree == NULL) {
        return 0;
    }
    
    int leftHeight = getHeight(tree->left);
    int rightHeight = getHeight(tree->right);
    
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int isBalanced(BinarySearchTree *tree) {
    if (tree == NULL) {
        return 1;
    }
    
    int leftHeight = getHeight(tree->left);
    int rightHeight = getHeight(tree->right);
    
    if (abs(leftHeight - rightHeight) <= 1 ) {
        return 1;
    }
    
    return 0;
}

BinarySearchTree *findMin(BinarySearchTree *tree) {
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

BinarySearchTree *deleteBinaryTree(BinarySearchTree *tree, int inf) {
    if (tree == NULL) {
        return tree;
    }
    
    if (inf < tree->inf.numb) {
        tree->left = deleteBinaryTree(tree->left, inf);
    } else if (inf > tree->inf.numb) {
        tree->right = deleteBinaryTree(tree->right, inf);
    } else {
        if (tree->left == NULL) {
            BinarySearchTree* temp = tree->right;
            free(tree);
            return temp;
        } else if (tree->right == NULL) {
            BinarySearchTree* temp = tree->left;
            free(tree);
            return temp;
        }
        
        BinarySearchTree* temp = findMin(tree->right);
        tree->inf = temp->inf;
        tree->right = deleteBinaryTree(tree->right, temp->inf.numb);
    }
    return tree;
}

void inorder(BinarySearchTree *tree) {
    if (tree == NULL) {
        return;
    }
    
    inorder(tree->left);
    printf("%d ", tree->inf.numb);
    inorder(tree->right);
}