/*faça um programa que, lê um arquivo texto , pegue e imprima na tela as seguintes 
informções : Nome , cidade , Gênero */

//includes
#include<stdio.h>
#include<stdlib.h>

//function prototypes

FILE * abrearquivo(char * name, char * mode);

//main function
int main(void){
    //variables 
    FILE * arqTexto;
    char nome[100];
    char cidade[100];
    char genero;

    //execution

    arqTexto = abrearquivo("info.txt","r");
    do{
        fscanf(arqTexto,"%[^,], %[^ ] %c\n",nome,cidade,&genero);
        printf("Nome: %s \nCidade: %s\nGênero: %c\n***********\n",nome,cidade,genero);
    } 
    while (!feof(arqTexto));
    fclose(arqTexto);

    return 0;
}

FILE * abrearquivo(char * name, char * mode){
    FILE * arq = fopen(name,mode);
    if(arq == NULL){
        fprintf(stderr,"Erro ao abrir arquivo !");
        exit(2);
    }
    return arq;
}   