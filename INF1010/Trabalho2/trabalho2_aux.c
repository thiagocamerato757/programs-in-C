#include "trabalho2_aux.h"
#include <stdio.h>
#include <stdlib.h>

// Function to initialize an empty binary search tree (BST)
abb *iniciatetree(void){
    return NULL;
}

// Function to create a new node with the specified integer value
abb* createNode(int value) {
    abb* newNode = (abb*)malloc(sizeof(abb));
    if (newNode) {
        newNode->info = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// Function to insert a new node with the specified value into the BST
abb* insertNode(abb* tree, int value) {
    if (tree == NULL) {
        return createNode(value);
    }

    if (value < tree->info) {
        tree->left = insertNode(tree->left, value);
    } else if (value > tree->info) {
        tree->right = insertNode(tree->right, value);
    }

    return tree;
}

// Function to find and return the maximum or minimum value node in the BST
abb* max_min_value(abb* tree, int mode) {
    if (!tree) return NULL;

    while ((mode == 1 && tree->right) || (mode == 0 && tree->left)) {
        tree = (mode == 1) ? tree->right : tree->left;
    }

    return tree;
}

// Function to find the predecessor or successor of a node with the specified value in the BST
abb* predecessor_successor(abb* tree, int mode, int value) {
    if (!tree) return NULL;

    abb* result = NULL;

    while (tree) {
        if (value < tree->info) {
            result = tree;
            tree = tree->left;
        } 
        else if (value > tree->info) {
            tree = tree->right;
        } 
        else {
            if (mode == 0) {
                if (tree->left) {
                    result = max_min_value(tree->left, 1); // Predecessor
                }
            } 
            else if (mode == 1) {
                if (tree->right) {
                    result = max_min_value(tree->right, 0); // Successor
                }
            }
            break;
        }
    }

    return result;
}

// Function to find and print the heights of two additional competitors to the one with height `infoB`
void findCompetitors(abb* tree, int infoB, int* visitedNodes) {
    abb* firstAdditional = NULL;
    abb* secondAdditional = NULL;
    abb* current = tree;

    while (current) {
        (*visitedNodes)++; // Count the visited nodes

        if (infoB < current->info) {
            secondAdditional = current;
            current = current->left;
        } else if (infoB > current->info) {
            firstAdditional = current;
            current = current->right;
        } else {
            // Found the competitor with the desired height
            if (current->left) {
                firstAdditional = max_min_value(current->left, 1); // Predecessor
            }
            if (current->right) {
                secondAdditional = max_min_value(current->right, 0); // Successor
            }
            break;
        }
    }

    printf("Competitor B: %d\n", infoB);

    if (firstAdditional) {
        printf("Competitor A: %d\n", firstAdditional->info);
    } else {
        printf("Competition invalid\n");
    }

    if (secondAdditional) {
        printf("Competitor C: %d\n", secondAdditional->info);
    } else {
        printf("Competition invalid\n");
    }
}

// Function to print the heights of all competitors in the BST in ascending order
void printTree(abb* tree) {
    if (tree) {
        printTree(tree->left);
        printf("%d ", tree->info);
        printTree(tree->right);
    }
}

// Function to free the memory allocated for the entire BST
void freeTree(abb* tree) {
    if (tree == NULL) {
        return;
    }
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
}
