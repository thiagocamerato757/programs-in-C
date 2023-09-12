#include"AUX_arvore_binaria_busca.h"
#include<stdlib.h>

BinarySearchTree *createTree(void){
    return NULL;
}

BinarySearchTree *searchItem(BinarySearchTree *tree, int item){
    if(tree->inf.numb == item){
        return tree;
    }
    else{
        if(tree->inf.numb > item){
            return searchItem(tree->left, item);

        }
        return searchItem(tree->right, item);
    }
    
}

void addNodeTree(BinarySearchTree *tree, int n){
    BinarySearchTree *new;
    new = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    new->inf.numb = n;
    if(!new) return;
    if(!tree){
        tree = new;
        tree->left = NULL;
        tree->right = NULL;
        return;
    }
    tree = searchItem(tree,new->inf.numb);
    if(tree->inf.numb > new->inf.numb){
        tree->left = new;
    }
    else{
        tree->right = new;
    }
    new->left = NULL;
    new->right = NULL;
    return;

}

