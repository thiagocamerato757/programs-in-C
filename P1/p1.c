//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes
FILE *abrearq(char *name, char *mode);
int CountIniciais(char *s);
char *lastName(char *s);
char *pegaIniciais(char *s);
char *createName(char *s);


//main function
int main(void){
    //variables
    FILE *arqIn;
    FILE *arqOut;
    char nome[100];
    char ID[100];
    float saldo;
    int tamanhoNome;
    char *newName;

    //execution
    arqIn = abrearq("banco.txt", "r");
    arqOut = abrearq("arqBinario.bin", "wb");

    while (fscanf(arqIn, "%[^:]:  %[^,] , %f\n", ID, nome, &saldo) == 3){
        newName = createName(nome);
        tamanhoNome = strlen(newName);
        printf("nome formatado: %s\nTamanho da String: %d\nSaldo de %s: R$%.2f\n", newName, tamanhoNome, nome, saldo);
        printf("**********************************************\n");
        fwrite(&tamanhoNome, sizeof(int), 1, arqOut);
        fwrite(newName, sizeof(char), tamanhoNome, arqOut);
        fwrite(&saldo, sizeof(float), 1, arqOut);
        free(newName);
    }

    newName = NULL;
    fclose(arqIn);
    fclose(arqOut);
    printf("Arquivo gravado com sucesso!\n");
    printf("Memórias liberadas com sucesso!\n");

    return 0;
}
// function to open an file
FILE *abrearq(char *name, char *mode){
    FILE *arq = fopen(name, mode);
    if (arq == NULL){
        fprintf(stderr, "Erro ao abrir arquivo!\n");
        exit(2);
    }
    return arq;
}
//function that usues recursion to count the inicials of a string
int CountIniciais(char *s){
    if (*s == '\0'){
        return 0;
    }
    else{
        if (*s >= 'A' && *s <= 'Z'){
            return 1 + CountIniciais(s + 1);
        }
        else{
            return 0 + CountIniciais(s + 1);
        }
    }
}

//functon that get's the last name of a string
char *lastName(char *s){
    int EspacosValidos = CountIniciais(s) - 1;
    int counter = 0;
    int length = strlen(s);
    int lastSpaceIndex;

    for (int i = 0; i < length; i++){
        if (*(s + i) == ' '){
            counter++;
            if (counter == EspacosValidos){
                lastSpaceIndex = i;
                break;
            }
        }
    }

    int j = 0;
    do{
        if (j != 0 && *(s + lastSpaceIndex + j) == ' '){
            break;
        }
        else{
            j++; // calculating the length of last name
        }
    } while (*(s + lastSpaceIndex + j) != '\0');

    int tamanhoSobrenome = j-1;
    char *sobrenome = (char *)malloc((tamanhoSobrenome + 3) * sizeof(char)); // 2 for ", " and 1 for null char
    if (sobrenome == NULL){
        fprintf(stderr, "Erro ao alocar memória do sobrenome !\n");
        exit(1);
    }

    for (int j = 0; j < tamanhoSobrenome; j++){
        *(sobrenome + j) = *(s + lastSpaceIndex + j + 1);
    }
    
    *(sobrenome + tamanhoSobrenome) = ',';
    *(sobrenome + tamanhoSobrenome + 1) = ' ';
    *(sobrenome + tamanhoSobrenome + 2) = '\0';

    return sobrenome;
}

//function to get all the inicials of a string
char *pegaIniciais(char *s){
    char *iniciais;
    int qtdIniciais = CountIniciais(s) - 1;
    
    iniciais = (char *)malloc((2 * qtdIniciais + 1) * sizeof(char));
    if (iniciais == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória das iniciais!\n");
        exit(1);
    }
    int i = 0;
    int j = 0;
    int espacosAteSobrenome = 0;
    while (espacosAteSobrenome  < qtdIniciais)
    {
        if(*(s+i) == ' ')
        {
            espacosAteSobrenome++;
        }
        if (*(s + i) >= 'A' && *(s + i) <= 'Z')
        {
            *(iniciais + j) = *(s + i);
            *(iniciais + j + 1) = '.';
            j += 2;
        }
        i++;
    }

    *(iniciais + j) = '\0';
    return iniciais;
}

//function to format a string (lastname, inicials.)
char *createName(char *s)
{
    char *nome = lastName(s);
    char *iniciais = pegaIniciais(s);
    char *criaNome;

    int tamanhoAlocado = strlen(nome) + strlen(iniciais) + 1;

    criaNome = (char *)malloc(tamanhoAlocado * sizeof(char));
    if (criaNome == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória do nome formatado!\n");
        exit(1);
    }

    strcpy(criaNome, nome);
    strcat(criaNome, iniciais);

    free(nome);
    free(iniciais);

    return criaNome;
}