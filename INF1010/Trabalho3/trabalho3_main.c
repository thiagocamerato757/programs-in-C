#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 1031

typedef struct Node {
    char* plate;
    struct Node* next;
} Node;

typedef struct {
    Node** plates;  // Vetor de ponteiros para listas vinculadas
    int size;       // Tamanho da tabela
} HashTable;

unsigned int hash(const char* key, int size) {
    unsigned int hash1 = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        hash1 = (hash1 * 101 + key[i]) % size;
    }

    return hash1;
}

// Inicializa a tabela de dispersão
HashTable* createHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->plates = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        ht->plates[i] = NULL;  // Inicializa todas as posições com NULL
    }
    return ht;
}

// Insere uma placa na tabela de dispersão e retorna o número de colisões durante a inserção
int insert(HashTable* ht, const char* plate) {
    int index = hash(plate, ht->size);
    int collisions = 0;  // Inicializa o contador de colisões

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->plate = strdup(plate);
    newNode->next = NULL;

    if (ht->plates[index] == NULL) {
        ht->plates[index] = newNode;  // Se a posição estiver vazia, insere o novo nó
    } else {
        // Se a posição já contém uma lista, insere no final da lista
        Node* current = ht->plates[index];
        while (current->next != NULL) {
            current = current->next;
            collisions++; // Contabiliza uma colisão
        }
        current->next = newNode;
        collisions++; // Contabiliza a colisão para a nova inserção
    }

    return collisions;  // Retorna o número de colisões reais durante a inserção
}

// Busca uma placa na tabela de dispersão e retorna o número de colisões durante a busca
// Retorna 1 se a placa foi encontrada, 0 caso contrário
int search(HashTable* ht, const char* plate) {
    int index = hash(plate, ht->size);
    int collisions = 0;  // Inicializa o contador de colisões durante a busca

    Node* current = ht->plates[index];
    while (current != NULL) {
        collisions++; // Contabiliza uma colisão
        if (strcmp(current->plate, plate) == 0) {
            return collisions;  // Placa encontrada
        }
        current = current->next;
    }
    return collisions;  // Placa não encontrada
}

// Libera a memória alocada para a tabela de dispersão
void destroyHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->plates[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current->plate);
            free(current);
            current = next;
        }
    }
    free(ht->plates);
    free(ht);
}

void printHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->plates[i];
        printf("Posição %d:", i);
        while (current != NULL) {
            printf(" %s ->", current->plate);
            current = current->next;
        }
        printf(" NULL");
        printf("\n");
    }
}

int main(void) {
    HashTable* ht = createHashTable(TABLE_SIZE);

    // Leitura das placas de um arquivo de texto
    FILE* file = fopen("placasMercosul.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    char plate[8];
    int totalInsertCollisions = 0;

    clock_t startInsert = clock(); // Medindo o tempo de inserção

    while (fscanf(file, "%s", plate) == 1) {
        int insertCollisions = insert(ht, plate);
        totalInsertCollisions += insertCollisions;
    }
    fclose(file);

    clock_t endInsert = clock();
    double insertionTime = ((double)(endInsert - startInsert)) / CLOCKS_PER_SEC;

    // Busca de exemplo
    char searchPlate[] = "DLM9G84";

    clock_t startSearch = clock(); // Medindo o tempo de busca
    int searchCollisions = search(ht, searchPlate);
    clock_t endSearch = clock();
    double searchTime = ((double)(endSearch - startSearch)) / CLOCKS_PER_SEC;

    printHashTable(ht);
    
    if (searchCollisions > 1) {
        printf("Placa encontrada na tabela com %d colisões.\n", searchCollisions);
    } else if (searchCollisions == 1) {
        printf("Placa encontrada na tabela sem colisões.\n");
    } else {
        printf("Placa não encontrada.\n");
    }

    // Imprime o total de colisões durante inserção
    printf("Total de colisões durante inserção: %d\n", totalInsertCollisions);
    printf("Tempo de inserção: %lf segundos\n", insertionTime);
    printf("Tempo de busca: %lf segundos\n", searchTime);

    // Libera a memória da tabela de dispersão
    destroyHashTable(ht);

    return 0;
}
