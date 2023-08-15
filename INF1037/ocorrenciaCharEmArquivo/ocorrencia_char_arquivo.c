/*Faça um programa que receba do usuário um arquivo texto e um caracter. Mostre na
tela quantas vezes aquele caractere ocorre dentro do arquivo*/

//includes
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//function prototypes
FILE * abrearq(char *nome,char*mode);

//main function
int main(void){
    //variables
    FILE * arq;
    char nome[100];
    char ch;
    char linha[1000];
    int ocorrencias = 0;

    //execution
    printf("escreva o nome do arquivo !\n");
    scanf(" %[^\n]",nome);
    printf("Digite o caracter que vc deseja saber a quantidade de ocorrências !\n");
    scanf(" %c",&ch);
    arq = abrearq(nome,"r");


    while (fgets(linha, sizeof(linha), arq) != NULL) {
        for (int i = 0; i < strlen(linha); i++) {
            if (linha[i] == ch) {
                ocorrencias++; //couting the ocurrences of ch
            }
        }
    }
    fclose(arq);
    printf("A quantidade de ocorrência de '%c' no arquivo é de : %d\n",ch,ocorrencias);

    return 0;
}

//function to open am archive and checks if it's openned properly 
FILE * abrearq(char *nome,char*mode){
    FILE *a = fopen(nome,mode);
    if(a == NULL){
        fprintf(stderr,"Erro ao abrir arquivo\n");
        exit(2);
    }
    return a;
}