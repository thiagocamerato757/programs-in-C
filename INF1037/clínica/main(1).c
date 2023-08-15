//includes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//creating simbolic variables
#define QTD_CHARS 81


struct medidas
{
    float cintura;
    float quadril;
};
typedef struct medidas Medidas;

struct cliente
{
    char nome[QTD_CHARS];
    int id;
    char genero;
    Medidas m;
};
typedef struct cliente Cliente;

//function prototypes
FILE* abrearq(char* nome, char* mode);
int countLines(char* fName);

//main function
int main(void) {
    //variables
    int lines;
    FILE* arqIn;
    FILE* arqOut;
    Cliente* cliente;

    //execution
    lines = countLines("pacientes.txt");
    if (lines == 0) {
        printf("O arquivo existe e está vazio!\n");
    }
    else if (lines == -1) {
        printf("O arquivo não existe !\n");
    }
    else {
        arqIn = abrearq("pacientes.txt", "r");
        arqOut = abrearq("pacientesBin.bin", "wb");

        if (arqIn != NULL && arqOut != NULL) {
            cliente = (Cliente*)malloc(sizeof(Cliente));
            if (cliente == NULL) {
                fprintf(stderr, "Erro ao alocar memória !\n");
                fclose(arqIn);
                fclose(arqOut);
                return 1;

            }
            fwrite(&lines, sizeof(int), 1, arqOut);
            while (!feof(arqIn)) {

                fscanf(arqIn, "%[^ ] %d %c %f %f \n", cliente->nome, &(cliente->id), &(cliente->genero),
                    &(cliente->m.cintura), &(cliente->m.quadril));
                fwrite(cliente, sizeof(Cliente), 1, arqOut);
                printf("%s %d %c %.2f %.2f\n", cliente->nome, cliente->id, cliente->genero, cliente->m.cintura, cliente->m.quadril);
            }
            printf("arquivo gravado com sucesso !\n");
            free(cliente);
        }
        fclose(arqIn);
        fclose(arqOut);
    }
    return 0;
}

//function to open a file
FILE* abrearq(char* nome, char* mode) {
    FILE* arquivo;
    arquivo = fopen(nome, mode);
    if (arquivo == NULL) {
        return NULL;
    }
    return arquivo;
}

//function that opens a file and counts its number of lines
int countLines(char* fName) {
    FILE* arq = fopen(fName, "r");
    if (arq == NULL) {
        return -1;
    }

    int contaLinha = 0;
    char ch;
    while ((ch = fgetc(arq)) != EOF) {
        if (ch == '\n') {
            contaLinha++;
        }
    }

    fclose(arq);
    return contaLinha;
}
