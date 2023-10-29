#include "trabalho3_aux.h"


unsigned int hash(char* key, int size) {
    unsigned int hash1 = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = key[i];

        if (ch >= 'A' && ch <= 'Z') {
            ch = ch - 'A';
        } else if (ch >= '0' && ch <= '9') {
            ch = ch - '0' + 26;
        }

        hash1 = (hash1 * 103 + ch) % size;
    }

    return hash1;
}

unsigned int secondaryHash(char* key, int size) {
    unsigned int hash2 = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = key[i];
        hash2 = (hash2 * SECONDARY_HASH_CONSTANT + ch) % size;
    }

    return hash2;
}

HashTable* createHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->plates = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        ht->plates[i] = NULL;
    }
    return ht;
}

int insert(HashTable* ht, char* plate) {
    int index = hash(plate, ht->size);
    int collisions = 0;  // Counter for collisions

    // If the slot is occupied, handle collisions using double hashing
    while (ht->plates[index] != NULL) {
        index = (index + secondaryHash(plate, ht->size)) % ht->size;
        collisions++;

        if (collisions >= ht->size) {
            return -1; // The table is full
        }
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->plate = strdup(plate);
    newNode->next = NULL;

    ht->plates[index] = newNode;

    return collisions; // Return the number of collisions for this insertion
}
int search(HashTable* ht, char* plate) {
    int index = hash(plate, ht->size);
    int originalIndex = index;
    int collisions = 0;  // Counter for collisions

    while (ht->plates[index] != NULL && collisions < ht->size) {
        if (strcmp(ht->plates[index]->plate, plate) == 0) {
            return collisions; // Return the number of collisions for this search
        }

        // Handle secondary collision by double hashing
        index = (index + secondaryHash(plate, ht->size)) % ht->size;
        collisions++;

        if (index == originalIndex) {
            // We've completed one loop; the plate is not in the table.
            return -1;
        }
    }

    return -1;  // Plate not found
}
int removePlate(HashTable* ht, char* plate) {
    int index = hash(plate, ht->size);
    int originalIndex = index;
    int collisions = 0;  // Counter for collisions

    while (ht->plates[index] != NULL && collisions < ht->size) {
        if (strcmp(ht->plates[index]->plate, plate) == 0) {
            // Found the plate, remove it
            free(ht->plates[index]->plate);
            free(ht->plates[index]);
            ht->plates[index] = NULL;
            return collisions; // Return the number of collisions for this removal
        }

        // Handle secondary collision by double hashing
        index = (index + secondaryHash(plate, ht->size)) % ht->size;
        collisions++;

        if (index == originalIndex) {
            // We've completed one loop; the plate is not in the table.
            return -1;
        }
    }

    return -1;  // Plate not found
}
void destroyHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->plates[i] != NULL) {
            free(ht->plates[i]->plate);
            free(ht->plates[i]);
        }
    }
    free(ht->plates);
    free(ht);
}
