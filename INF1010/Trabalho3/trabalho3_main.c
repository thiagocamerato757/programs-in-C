#include "trabalho3_aux.h"

int main(void) {
    HashTable* ht = createHashTable(TABLE_SIZE);

    FILE* file = fopen("placasMercosul.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    char plate[8];
    int totalInsertCollisions = 0;
    int plateCount = 0;

    clock_t startInsert = clock();

    while (fscanf(file, "%s", plate) == 1) {
        int insertCollisions = insert(ht, plate);
        totalInsertCollisions += insertCollisions;
        plateCount++;

        if (plateCount == 128 || plateCount == 256 || plateCount == 512) {
            printf("Total de colisões ao inserir %d placas: %d\n", plateCount, totalInsertCollisions);
        }
    }

    clock_t endInsert = clock();
    double insertTime = ((double)(endInsert - startInsert)) / CLOCKS_PER_SEC;

    fclose(file);

    printf("Total de placas inseridas: %d\n", plateCount);
    printf("Total de colisões durante inserção: %d\n", totalInsertCollisions);
    printf("Tempo total de inserção: %lf segundos\n", insertTime);

    // Perform searches and measure time
    int totalSearchCollisions = 0;
    clock_t startSearch = clock();

   

    clock_t endSearch = clock();
    double searchTime = ((double)(endSearch - startSearch)) / CLOCKS_PER_SEC;

    printf("Total de colisões durante busca: %d\n", totalSearchCollisions);
    printf("Tempo total de busca: %lf segundos\n", searchTime);

    // Remove a plate
    char plateToRemove[8]; // Replace with the plate you want to remove
    printf("Digite a placa a ser removida: ");
    scanf("%s", plateToRemove);
    int removeCollisions = removePlate(ht, plateToRemove);
    if (removeCollisions >= 0) {
        printf("Total de colisões durante remoção: %d\n", removeCollisions);
    } else {
        printf("A placa a ser removida não foi encontrada na tabela.\n");
    }

    char plateToFind[8];
    printf("Digite a placa a ser encontrada: ");
    scanf("%s", plateToFind);
    int searchCollisions = search(ht, plateToFind);
    if (searchCollisions >= 0) {
        printf("Total de colisões durante remoção: %d\n", searchCollisions);
    } else {
        printf("A placa a ser removida não foi encontrada na tabela.\n");
    }

    // Liberate the memory of the hash table
    destroyHashTable(ht);

    return 0;
}