#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 1031
#define SECONDARY_HASH_CONSTANT 31
typedef struct Node {
    char* plate;
    struct Node* next;
} Node;

typedef struct {
    Node** plates;  // Array of pointers for open addressing
    int size;       // Size of the table
} HashTable;

HashTable* createHashTable(int size);
int insert(HashTable* ht, char* plate);
int search(HashTable* ht, char* plate);
int removePlate(HashTable* ht, char* plate);
void destroyHashTable(HashTable* ht);