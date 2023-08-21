//includes
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//structed data
struct Aluno {
    int matricula;
    char nome[80];
    char endereco[120];
    char telefone[20];
};
typedef struct Aluno aluno;

//function prototypes
aluno ** criaTabela(int qtdAlunos);
void preencheTabela(aluno ** tab, int qtdAlunos);
void imprimeStringRecursivo(char *str);
int comprimentoStringRecursivo(char *str);
int buscaAluno(aluno **tab, char *nome, int qtdAlunos);
int buscaAluno(aluno **tab, char *nome, int qtdAlunos);
void removeAluno(aluno **tab, int qtdAlunos, int matricula);

//main function
int main(void) {
    //variables
    int numAlunos;
    aluno **alunos;

    //execution
    printf("Digite o número de alunos: ");
    scanf("%d", &numAlunos);
    alunos = criaTabela(numAlunos);
    if(!alunos){
        printf("eero ao alocar memória!\n");
        exit(1);
    }
    preencheTabela(alunos,numAlunos);
    imprimeTabela(alunos, numAlunos);
    //deallocating memory
    for (int i = 0; i < numAlunos; i++) {
        free(alunos[i]);
    }
    free(alunos);

    return 0;
}

aluno ** criaTabela(int qtdAlunos){
    //Dynamic allocation of double pointer
    aluno **alunos = (aluno **)malloc(qtdAlunos * sizeof(aluno *));
    if (alunos == NULL) {
        return NULL;
    }

    for (int i = 0; i < qtdAlunos; i++) {
        alunos[i] = (aluno *)malloc(sizeof(aluno));
        if (alunos[i] == NULL) {
            NULL;
        }
    }
    return alunos;
}

void preencheTabela(aluno ** tab, int qtdAlunos){
    for (int i = 0; i < qtdAlunos; i++) {
        printf("Aluno %d:\n", i + 1);
        printf("Matrícula: ");
        scanf("%d", &tab[i]->matricula);
        printf("Nome: ");
        scanf(" %[^\n]", tab[i]->nome);
        printf("Endereço: ");
        scanf(" %[^\n]", tab[i]->endereco);
        printf("Telefone: ");
        scanf(" %[^\n]", tab[i]->telefone);
    }
}

//function to recursivelly print a string 
void imprimeStringRecursivo(char *str) {
    if (*str == '\0') {
        return;
    }
    printf("%c", *str);
    imprimeStringRecursivo(str + 1);
}

//function to calculate the size of the string 
int comprimentoStringRecursivo(char *str) {
    if (*str == '\0') {
        return 0;
    }
    return 1 + comprimentoStringRecursivo(str + 1);
}

//function to find a student by his name 
int buscaAluno(aluno **tab, char *nome, int qtdAlunos){
    int cmp;
    for(int i = 0; i < qtdAlunos; i++){
        cmp = strcmp(tab[i]->nome,nome);
        if(cmp == 1){
            return i;
        }
    }
    return -1;
}

//function to remove a student from the table by his ID
void removeAluno(aluno **tab, int qtdAlunos, int matricula){
    for(int i = 0;i < qtdAlunos;i++){
        if(matricula == tab[i]->matricula){
            free(tab[i]);
        }
    }
}

void imprimeTabela(aluno **tab, int qtdAlunos){
    printf("\nDados dos alunos:\n");
    for (int i = 0; i < qtdAlunos; i++) {
        printf("Aluno %d:\n", i + 1);
        printf("Matrícula: %d\n", tab[i]->matricula);
        printf("Nome: ");
        imprimeStringRecursivo(tab[i]->nome);
        printf("\n");
        printf("Endereço: ");
        imprimeStringRecursivo(tab[i]->endereco);
        printf("\n");
        printf("Telefone: ");
        imprimeStringRecursivo(tab[i]->telefone);
        printf("\n");
        printf("Comprimento do Nome: %d\n", comprimentoStringRecursivo(tab[i]->nome));
        printf("Comprimento do Endereço: %d\n", comprimentoStringRecursivo(tab[i]->endereco));
        printf("Comprimento do Telefone: %d\n", comprimentoStringRecursivo(tab[i]->telefone));
        printf("\n");
    }
}