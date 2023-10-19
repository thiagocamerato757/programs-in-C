#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 1024

typedef struct HashNode {
    char key[8];
    int value;
    struct HashNode *next;
} HashNode;

HashNode *hash_table[TABLE_SIZE];

unsigned long hash_function(char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // DJB2 hash function
    }

    return hash % TABLE_SIZE;
}

void insert(char *key) {
    unsigned long index = hash_function(key);

    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    if (new_node == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    strncpy(new_node->key, key, 8);
    new_node->value = 1;
    new_node->next = NULL;

    if (hash_table[index] == NULL) {
        hash_table[index] = new_node;
    } else {
        HashNode *current = hash_table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

int search(char *key) {
    unsigned long index = hash_function(key);

    HashNode *current = hash_table[index];
    while (current != NULL) {
        if (strncmp(current->key, key, 8) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s arquivo_de_placas.txt\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    char line[10];
    int collisions = 0;
    clock_t start_time, end_time;
    double insertion_time, search_time;

    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }

    start_time = clock();

    while (fgets(line, sizeof(line), file) != NULL) {
        line[8] = '\0';
        if (search(line) == 0) {
            insert(line);
        } else {
            collisions++;
        }
    }

    end_time = clock();
    insertion_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    rewind(file); // Reset file position for search

    start_time = clock();

    while (fgets(line, sizeof(line), file) != NULL) {
        line[8] = '\0';
        search(line);
    }

    end_time = clock();
    search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    fclose(file);

    printf("Total de colisões: %d\n", collisions);
    printf("Tempo de inclusão: %.6f segundos\n", insertion_time);
    printf("Tempo de busca: %.6f segundos\n", search_time);

    return 0;
}
