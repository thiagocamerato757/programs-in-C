#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 1031

typedef struct {
    char** plates;  // Vetor de ponteiros para strings de placas
    int size;       // Tamanho da tabela
    int count;      // Número de elementos na tabela
} HashTable;



unsigned int hash(HashTable* ht, char* key, int table_size, int attempt) {
    unsigned int index = (unsigned int)key[0] % table_size;
    int i = 1;

    while (ht->plates[index] != NULL) {
        index = (index + (unsigned int)key[i] + i) % table_size;
        i++;
    }

    return index;
}


// Inicializa a tabela de dispersão
HashTable* createHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->count = 0;
    ht->plates = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        ht->plates[i] = NULL;  // Inicializa todas as posições como nulas
    }
    return ht;
}

// Insere uma placa na tabela de dispersão e retorna o número de colisões
int insert(HashTable* ht, const char* plate) {
    int attempt = 0;
    int index = hash(plate, ht->size, attempt);

    // Enquanto a posição estiver ocupada, avance para a próxima
    while (ht->plates[index] != NULL) {
        attempt++;
        index = (index + 1) % ht->size;  // Tratamento de colisões linear
    }

    ht->plates[index] = strdup(plate);
    ht->count++;

    return attempt;  // Retorna o número de colisões
}

// Busca uma placa na tabela de dispersão
int search(HashTable* ht, const char* plate) {
    int attempt = 0;
    int index = hash(plate, ht->size, attempt);

    while (ht->plates[index] != NULL) {
        if (strcmp(ht->plates[index], plate) == 0) {
            return 1;  // Encontrou a placa
        }
        attempt++;
        index = hash(plate, ht->size, attempt);
    }
    return 0;  // Placa não encontrada
}

// Libera a memória alocada para a tabela de dispersão
void destroyHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        free(ht->plates[i]);
    }
    free(ht->plates);
    free(ht);
}

void printHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->plates[i] != NULL) {
            printf("Posição %d: %s\n", i, ht->plates[i]);
        } else {
            printf("Posição %d: Vazia\n", i);
        }
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
    clock_t startTime, endTime;
    int totalCollisions = 0;  // Contador de colisões

    while (fscanf(file, "%s", plate) == 1) {
        startTime = clock();
        int collisions = insert(ht, plate);
        totalCollisions += collisions;
        endTime = clock();
    }
    fclose(file);

    // Busca de exemplo
    char searchPlate[] = "PVY7T80";
    startTime = clock();
    int result = search(ht, searchPlate);
    endTime = clock();

    if (result) {
        printf("Placa encontrada na tabela.\n");
    } else {
        printf("Placa não encontrada.\n");
    }
    
    //printHashTable(ht);
    
    // Imprime o total de colisões
    printf("Total de colisões: %d\n", totalCollisions);

    // Libera a memória da tabela de dispersão
    destroyHashTable(ht);

    return 0;
}
