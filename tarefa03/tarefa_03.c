//Thiago Pereira Camerato
//2212580 
//33B 


//includes 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//creating simbolic variable
#define TAMANHO_STRING 81

//structed data 
struct bioData {
    float altura;
    float peso;
};

typedef struct bioData BioData;

struct client {
    char nome[TAMANHO_STRING];
    BioData info;
};

typedef struct client Client;


//function prototypes
FILE* abrearq(char* str, char* mode);
int countLines(char* fName);
Client** lerMontarVetor(char * file, int linhas);
void imprimeVetor(Client** clients, int qtd);
float mean(Client ** p, int qtd);
float standardDeviation(Client** data, int qtd , float media);
int comparaAltura(Client* clienteA, float clienteB);
int buscaBinaria(Client** vetor, int qtd, float altura);
void freeMem(Client** cl, int lines);


//main function 
int main(void) {
    //variables
    int lines;
    Client ** vector;
    float mediaPeso;
    float desvioPadrao;
    int indicePessoaMaiorPeso;
    float alturaEspecificada;

    //execution
    lines = countLines("clientes.txt");
    if(lines == 0){
        printf("O arquivo existe e está vazio!\n");
        printf("Média e Desvio padrão não calculável(divisão por zero !)\n");
    }
    else if(lines == -1){
        printf("O arquivo não existe!\n");
    }
    else{
        printf("Clientes :\n");
        vector = lerMontarVetor("clientes.txt", lines);
        imprimeVetor(vector, lines);
        mediaPeso = mean(vector,lines);
        printf("Média do peso : %.2f kg",mediaPeso);
        desvioPadrao = standardDeviation(vector,lines,mediaPeso);
        printf("     Desvio padrão do peso : %.2f\n",desvioPadrao);
        printf("Digite a altura para procurarmos a pessoa com o maior peso dessa altura!\n");
        scanf("%f",&alturaEspecificada);
        indicePessoaMaiorPeso = buscaBinaria(vector,lines,alturaEspecificada);
        if (indicePessoaMaiorPeso != -1) {
        printf("Registro da pessoa de maior peso com altura %.2f m : %s, %.2f m %.1f kg\n", alturaEspecificada,
               vector[indicePessoaMaiorPeso]->nome, vector[indicePessoaMaiorPeso]->info.altura, 
               (float)vector[indicePessoaMaiorPeso]->info.peso);
    } 
        else {
        printf("Nenhum paciente encontrada com a altura %.2f m\n ", alturaEspecificada);
        }

        freeMem(vector, lines);   
    }
    return 0;
}

//function to open a file
FILE* abrearq(char* str, char* mode) {
    FILE* arq = fopen(str, mode);
    if (arq == NULL) {
        return NULL;
    }
    return arq;
}

//function that opens a file and count the it's number of lines
int countLines(char * fName) {
    FILE * arq = abrearq(fName,"r");
    if(arq == NULL){
        return -1;
    }
    char ch;
    int contaLinha = 0;
    while ((ch = fgetc(arq)) != EOF) {
        if (ch == '\n') {
            contaLinha++;
        }
    }
    fclose(arq);
    return contaLinha;
}
//function that creates an array of pointers and includes all related data in it 
Client** lerMontarVetor(char * file, int linhas) {
    Client ** vetorPointer;
    char name[TAMANHO_STRING];
    float altura;
    int peso;
    int i = 0;
    FILE * arqText = abrearq(file,"r");

    vetorPointer = (Client **)malloc(linhas*sizeof(Client * ));
    if(vetorPointer == NULL){
        return NULL;
        fclose(arqText);
    }
    while (fscanf(arqText,"%[^:]:%f%d\n", name, &altura, &peso) == 3) {
        vetorPointer[i] = (Client*)malloc(sizeof(Client));
        if (vetorPointer[i] == NULL) {
            fclose(arqText);
            return NULL;
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
    fclose(arqText);
    return vetorPointer;
}

//function to print the array of pointers
void imprimeVetor(Client** clients, int qtd) {
  
    
    printf(" --------------------------------------\n");
    for (int i = 0; i < qtd; i++) {
    
    printf("| %-15s-> %6.2f m %6.1f kg |\n", clients[i]->nome, clients[i]->info.altura, (float)clients[i]->info.peso);
    }
    printf(" --------------------------------------\n");
    
}

//function to calculate the mean of the weights 
float mean(Client ** p, int qtd){
   
    float soma = 0;
    for(int i = 0; i < qtd; i++ ){
        soma += (float) p[i]->info.peso;
    }
    return (soma/(float)qtd);

}

//function to calculate the standart Deviation of the weights
float standardDeviation(Client** data, int qtd , float media) {
    float stdDeviation = 0;
    
    for (int i = 0; i < qtd; i++) {
        stdDeviation += (data[i]->info.peso - media) * (data[i]->info.peso - media);
    }
    
    stdDeviation = sqrt(stdDeviation / qtd);
    return stdDeviation;
   

}

// Compare the heights of two clients
// Returns:
//   -1 if clienteA's height is smaller than clienteB's height
//    1 if clienteA's height is greater than clienteB's height
//    0 if clienteA's height is equal to clienteB's height
int comparaAltura(Client* clienteA, float clienteB) {
    // Comparison of heights
    if (clienteA->info.altura < clienteB){
        return -1;
    } else if (clienteA->info.altura > clienteB ) {
        return 1;
    } else {
        return 0;
    } }

// Binary search to find the index of the person with the highest weight at a given height
// Returns the index of the person with the highest weight at the specified height
// If no person is found with the specified height, returns -1
int buscaBinaria(Client** vetor, int qtd, float altura) {
    int inicio = 0;
    int fim = qtd - 1;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        // Check if the height at the middle index matches the specified height
        if (comparaAltura(vetor[meio], altura) == 0) {
            // Sequential search to find the person with the highest weight for the specified height
            int indice = meio;
            while (indice < fim && comparaAltura(vetor[indice + 1], altura) == 0) {
                if (vetor[indice + 1]->info.peso > vetor[indice]->info.peso) {
                    indice++;
                } 
                else {
                    break;
                }
            }
            return indice;
        }

        // Check if the height at the middle index is greater than the specified height
        if (comparaAltura(vetor[meio], altura) > 0) {
            fim = meio - 1;
        }
        // Check if the height at the middle index is less than the specified height
        else {
            inicio = meio + 1;
        }
    }

    return -1; // Height not found
}

//function to dealocate the dynamic alocated memory
void freeMem(Client** cl, int lines) {
    for (int i = 0; i < lines; i++) {
        free(cl[i]);
        cl[i] = NULL;
    }
    free(cl);
    cl = NULL;
    printf("Todas as memórias foram liberadas!\n");
}
