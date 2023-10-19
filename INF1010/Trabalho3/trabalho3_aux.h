#define TABLE_SIZE 1024

typedef struct HashNode {
    char key[8];
    int value;
    struct HashNode *next;
} HashNode;

HashNode *hash_table[TABLE_SIZE];