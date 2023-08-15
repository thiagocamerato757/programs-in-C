/*Faça um programa que abra um arquivo HTML e elimine todas as “tags” do texto, ou
seja, o programa deve gerar um novo arquivo em disco que elimine todas as tags Html
que são caracterizadas por comandos entre “<” e “>”*/

//includes
#include<stdio.h>
#include<stdlib.h>


//function prototypes
FILE * abrearq(char *nome,char*mode);

//main function
int main(void){
    //variables
    FILE * arqHTML;
    FILE * arqTXT;
    char ch;
    int dentroDaTag = 0;
    
    //execution
    arqHTML = abrearq("arqHTML.html","r");
    arqTXT = abrearq("resultado.txt","w");

    while((ch = fgetc(arqHTML))!= EOF){
        if (ch == '<') {
            dentroDaTag = 1;
        } 
        else if (ch == '>') {
            dentroDaTag = 0;
        } 
        else if (dentroDaTag == 0) {
            // writing char without tags in txt file
            fwrite(&ch,sizeof(char),1,arqTXT);
        }
    }
    
    fclose(arqHTML);
    
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