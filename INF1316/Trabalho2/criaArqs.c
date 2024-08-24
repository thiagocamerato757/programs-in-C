#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar um número aleatório entre min e max, inclusive
int gerarNumeroAleatorio(int min, int max) {
    return rand() % (max - min - 1) + min;
}

// Função para gerar um caractere aleatório 'R' ou 'W'
char gerarCaractereAleatorio() {
    return rand() % 2 == 0 ? 'R' : 'W';
}

// Função para preencher um arquivo com 100 linhas de dados aleatórios
void preencherArquivo(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    for (int i = 0; i < 100; i++) {
        int numero = gerarNumeroAleatorio(1, 16);
        char caractere = gerarCaractereAleatorio();
        fprintf(arquivo, "%02d %c\n", numero, caractere);
    }

    fclose(arquivo);
}

int main() {
//Inicializar o gerador de números aleatórios
    srand(time(NULL));

    //Preencher os três arquivos
    preencherArquivo("P1.txt");
    preencherArquivo("P2.txt");
    preencherArquivo("P3.txt");

    printf("Arquivos preenchidos com sucesso!\n");

    return 0;
}
