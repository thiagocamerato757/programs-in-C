#include <stdio.h>
#include <stdlib.h>


// Definição da estrutura de dados do aluno
struct Aluno {
    int matricula;
    char nome[80];
    char endereco[120];
    char telefone[20];
};

// Função para imprimir uma string de forma recursiva
void imprimeStringRecursivo(const char *str) {
    if (*str == '\0') {
        return;
    }
    printf("%c", *str);
    imprimeStringRecursivo(str + 1);
}

// Função para calcular o comprimento de uma string de forma recursiva
int comprimentoStringRecursivo(const char *str) {
    if (*str == '\0') {
        return 0;
    }
    return 1 + comprimentoStringRecursivo(str + 1);
}

int main() {
    int numAlunos;

    printf("Digite o número de alunos: ");
    scanf("%d", &numAlunos);

    // Alocação de memória para o vetor de ponteiros de alunos
    struct Aluno **alunos = (struct Aluno **)malloc(numAlunos * sizeof(struct Aluno *));
    if (alunos == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Preenchimento dos dados dos alunos
    for (int i = 0; i < numAlunos; i++) {
        alunos[i] = (struct Aluno *)malloc(sizeof(struct Aluno));
        if (alunos[i] == NULL) {
            printf("Erro ao alocar memória.\n");
            return 1;
        }

        printf("Aluno %d:\n", i + 1);

        printf("Matrícula: ");
        scanf("%d", &alunos[i]->matricula);

        printf("Nome: ");
        scanf(" %[^\n]", alunos[i]->nome);

        printf("Endereço: ");
        scanf(" %[^\n]", alunos[i]->endereco);

        printf("Telefone: ");
        scanf(" %[^\n]", alunos[i]->telefone);
    }

    // Impressão dos dados dos alunos
    printf("\nDados dos alunos:\n");
    for (int i = 0; i < numAlunos; i++) {
        printf("Aluno %d:\n", i + 1);
        printf("Matrícula: %d\n", alunos[i]->matricula);
        printf("Nome: ");
        imprimeStringRecursivo(alunos[i]->nome);
        printf("\n");
        printf("Endereço: ");
        imprimeStringRecursivo(alunos[i]->endereco);
        printf("\n");
        printf("Telefone: ");
        imprimeStringRecursivo(alunos[i]->telefone);
        printf("\n");
        printf("Comprimento do Nome: %d\n", comprimentoStringRecursivo(alunos[i]->nome));
        printf("Comprimento do Endereço: %d\n", comprimentoStringRecursivo(alunos[i]->endereco));
        printf("Comprimento do Telefone: %d\n", comprimentoStringRecursivo(alunos[i]->telefone));
        printf("\n");
    }

    // Liberação da memória alocada
    for (int i = 0; i < numAlunos; i++) {
        free(alunos[i]);
    }
    free(alunos);

    return 0;
}
