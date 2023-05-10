/*Faça um programa para ler um arquivo linha a linha e escrevê‐la na tela.*/

//includes
#include<stdio.h>
#include<stdlib.h>

//function prototypes
FILE * abrearq(char *nome,char*mode);

//main function
int main(void){
    //variables
    FILE *arq;
    char nome[100];
    char linha[1000];

    //executition
    printf("Digite o nome do arquivo ! \n");
    scanf(" %[^\n]",nome);
    arq = abrearq(nome,"r");
    printf("TEXTO DO ARQUIVO:\n");
    while(fgets(linha,sizeof(linha),arq) != NULL){
        printf("%s\n",linha); //printing each line in the terminal 
    }
    fclose(arq);
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