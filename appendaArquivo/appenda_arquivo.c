/*Faça um programa que receba dois arquivos do usuário, e crie um terceiro arquivo
com o conteúdo dos dois primeiros juntos*/

//includes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//function prototypes
FILE * abrearq(char *nome,char*mode);

//main function
int main(void){
    //variables
    FILE *arq1;
    FILE *arq2;
    char linha[10000];

    //execution
    arq1 = abrearq("textoDestino.txt","a");
    arq2 = abrearq("textoOrigem.txt","r+");

    fputc('\n', arq1); // Write the newline character to the destination file
    while(fgets(linha, sizeof(linha), arq2) != NULL){
        printf("%s",linha);
        fwrite(linha,sizeof(char),strlen(linha),arq1);
    }

    fclose(arq2);
    fclose(arq1);
    
    return 0;
}

//function to open am archive and checks if it's openned properly 
FILE * abrearq(char *nome,char*mode){
    FILE *a = fopen(nome,mode);
    if(a == NULL){
        fprintf(stderr,"Erro ao abrir arquivo\n");
        exit(1);
    }
    return a;
}