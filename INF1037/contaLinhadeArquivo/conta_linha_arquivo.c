/* Faça um programa que receba do usuário um arquivo texto e mostre na tela quantas
linhas esse arquivo possui */

//includes
#include<stdio.h>
#include<stdlib.h>

//funtion prototypes
FILE * abrearq(char *nome,char*mode);

//main function 
int main(void){
    //variables 
    FILE *arq;
    int contaLinha = 0;
    char Nome[100];
    char ch;

    //execution
    printf("escreva o nome do arquivo !\n");
    scanf(" %[^\n]",Nome);
    arq = abrearq(Nome,"r");
    while ((ch = fgetc(arq)) != EOF) {
        if (ch == '\n') {
            contaLinha++; //counting how many lines are in a arq.txt
        }
    }
    
    printf("O arquivo tem %d linhas \n",contaLinha);
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