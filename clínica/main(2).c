
//includes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//creating symbolic variables
#define QTD_CHARS 81

struct medidas {
    float cintura;
    float quadril;
};
typedef struct medidas Medidas;

struct cliente {
    char nome[QTD_CHARS];
    int id;
    char genero;
    Medidas m;
};
typedef struct cliente Cliente;

//function prototypes
FILE* abrearq(char* nome, char* mode);
void whr(Cliente** cli, char genero, int qtdClients, float* media, float* desvio);
void liberamemoria(Cliente** cl, int qtd);

//main function
int main(void) {
    //variables
    FILE* arqBin;
    int linhaBin;
    Cliente** clientePointer;
    float mean = 0;
    float stdDeviation = 0;

    //execution

    arqBin = abrearq("pacientesBin.bin", "rb");

    if (arqBin == NULL) {
        fprintf(stderr, "não possível de abrir o arquivo!\n");
        exit(2);
    }
    else {

        if (fread(&linhaBin, sizeof(int), 1, arqBin) == 1) {


            clientePointer = (Cliente**)malloc(linhaBin * sizeof(Cliente*));
            if (clientePointer == NULL) {
                fprintf(stderr, "Erro ao alocar memoria do vetor de ponteiros!\n");
                fclose(arqBin);
                return 1;
            }

            for (int i = 0; i < linhaBin; i++) {
                clientePointer[i] = (Cliente*)malloc(sizeof(Cliente));
                if (clientePointer[i] == NULL) {
                    liberamemoria(clientePointer, i + 1);
                    fprintf(stderr, "Erro ao alocar memoria do cliente %d\n", i);
                    fclose(arqBin);
                    return 1;
                }

                if (fread(clientePointer[i], sizeof(Cliente), 1, arqBin) != 1) {
                    liberamemoria(clientePointer, i + 1);
                    fprintf(stderr, "Erro ao ler dados do cliente %d\n", i + 1);
                    fclose(arqBin);
                    return 1;
                }

            }
            fclose(arqBin);
            printf("*******************************************************\n");
            whr(clientePointer, 'F', linhaBin, &mean, &stdDeviation);
            printf("Media do índece WHR no sexo feminino : %.2f\n", mean);
            printf("Desvio padrão do índece WHR no sexo feminino : %.2f\n", stdDeviation);
            printf("*******************************************************\n");
            whr(clientePointer, 'M', linhaBin, &mean, &stdDeviation);
            printf("Media do índece WHR no sexo masculino : %.2f\n", mean);
            printf("Desvio padrão do índece WHR no sexo masculino : %.2f\n", stdDeviation);
            printf("*******************************************************\n");
            liberamemoria(clientePointer, linhaBin);
        }
    }
    return 0;
}

//function to open a file
FILE* abrearq(char* nome, char* mode) {
    FILE* arquivo;
    arquivo = fopen(nome, mode);
    return arquivo;
}


void whr(Cliente** cli, char genero, int qtdClients, float * media, float * desvio) {
    float calculo = 0;
    float risco = 0;
    float soma = 0;
    int contasex = 0;
    float variacao = 0;

    if (genero == 'F') {
        risco = 0.85;
    }
    else if (genero == 'M') {
        risco = 1.00;
    }
    for (int i = 0; i < qtdClients; i++) {
        if (cli[i]->genero == genero){
            calculo = cli[i]->m.cintura / cli[i]->m.quadril;
            if (calculo > risco) {
                printf("%s corre risco de saúde !\n", cli[i]->nome);
            }
            contasex += 1;
            soma += calculo;
        }
    }
    *media = (soma / contasex);

    for (int j = 0; j < qtdClients; j++) {
        if (cli[j]->genero == genero) {
            calculo = cli[j]->m.cintura / cli[j]->m.quadril;
            variacao += (calculo - (*media)) * (calculo - (*media));
        }
    }

    *desvio = sqrt(variacao / contasex);

}


void liberamemoria(Cliente** cl, int qtd) {
    for (int i = 0; i < qtd; i++) {
        free(cl[i]);
    }

    free(cl);
    printf("Memoria liberada com sucesso!\n");
}