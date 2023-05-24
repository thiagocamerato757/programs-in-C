#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAMANHO_STRING 81

struct bioData {
    float altura;
    int peso;
};

typedef struct bioData BioData;

struct client {
    char nome[TAMANHO_STRING];
    BioData info;
};

typedef struct client Client;

FILE* abrearq(char* str, char* mode);
int countLines(char* fName);
Client** lerMontarVetor(FILE* file, int linhas);
void imprimeVetor(Client** clients, int qtd);
float mean(Client ** p, int qtd);
float standardDeviation(Client** data, int qtd , float media);
void freeMem(Client** cl, int lines);

int main(void) {
    FILE* arqText;
    int lines;
    Client** vector;
    float mediaPeso;
    float desvioPadrao;

    lines = countLines("clientes.txt");
    arqText = abrearq("clientes.txt", "r");
    vector = lerMontarVetor(arqText, lines);
    imprimeVetor(vector, lines);
    mediaPeso = mean(vector,lines);
    printf("Média do peso : %.2f kg",mediaPeso);
    desvioPadrao = standardDeviation(vector,lines,mediaPeso);
    printf("     Desvio padrão do peso : %.2f\n",desvioPadrao);

    freeMem(vector, lines);
    fclose(arqText);
    return 0;
}

FILE* abrearq(char* str, char* mode) {
    FILE* arq = fopen(str, mode);
    if (arq == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo!\n");
        exit(2);
    }
    return arq;
}

int countLines(char * fName) {
    FILE * arq = abrearq(fName,"r");
    char ch;
    int contaLinha = 0;
    while ((ch = fgetc(arq)) != EOF) {
        if (ch == '\n') {
            contaLinha++; //counting how many lines are in a arq.txt
        }
    }
    contaLinha++;
    fclose(arq);
    return contaLinha;
}

Client** lerMontarVetor(FILE* file, int linhas) {
    Client** vetorPointer;
    char name[TAMANHO_STRING];
    float altura;
    int peso;

    vetorPointer = (Client**)malloc(linhas * sizeof(Client*));
    if (vetorPointer == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os clientes.\n");
        exit(1);
    }
    int i = 0;
    while (fscanf(file,"%[^:]:%f%d\n", name, &altura, &peso) == 3) {
        vetorPointer[i] = (Client*)malloc(sizeof(Client));
        if (vetorPointer[i] == NULL) {
            fprintf(stderr, "Erro ao alocar memória para o cliente número %d.\n", i);
            exit(1);
        }

        int j;
        for (j = 0; name[j] != '\0'; j++) {
            vetorPointer[i]->nome[j] = name[j];
        }
        vetorPointer[i]->nome[j] = '\0';

        vetorPointer[i]->info.altura = altura;
        vetorPointer[i]->info.peso = peso;

        i++;
    }

    return vetorPointer;
}

void imprimeVetor(Client** clients, int qtd) {
    printf(" Clientes :\n");
    printf(" --------------------------------------\n");
    for (int i = 0; i < qtd; i++) {
        printf("| %-15s-> %6.2f m %6.1f kg |\n", clients[i]->nome, clients[i]->info.altura, (float)clients[i]->info.peso);
    }
    printf(" --------------------------------------\n");
}

float mean(Client ** p, int qtd){
    float soma = 0;
    for(int i = 0; i < qtd; i++ ){
        soma += (float) p[i]->info.peso;
    }
    return (soma/(float)qtd);
}

float standardDeviation(Client** data, int qtd , float media) {
    float varia = 0.0;

    for (int i = 0; i < qtd; i++) {
        varia += (data[i]->info.peso - media) * (data[i]->info.peso - media);
    }

    varia /= qtd;
    float stdDeviation = 0;

    for (int i = 0; i < qtd; i++) {
        stdDeviation += (data[i]->info.peso - media) * (data[i]->info.peso - media);
    }

    stdDeviation = sqrt(stdDeviation / qtd);
    return stdDeviation;
}


void freeMem(Client** cl, int lines) {
    for (int i = 0; i < lines; i++) {
        free(cl[i]);
        cl[i] = NULL;
    }
    free(cl);
    cl = NULL;
    printf("Todas as memórias foram liberadas!\n");
}
