//includes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//creating simbolic variables
#define TAMANHO_LIST 9

//function prototypes 
FILE * abrearq(char *file,char*mode);
void criaNomeBin(char * str);
int achaMax(int *a, int tamanho);

//main function
int main(void){
    //variables
    FILE *arqTxt;
    FILE *arqBin;
    char nomePessoa[100] = "";
    int list[TAMANHO_LIST];
    int max = 0;

    //execution 
    arqTxt = abrearq("dadosDrone2.txt","r");
    fscanf(arqTxt,"%[^:]:",nomePessoa);
    printf("%s :",nomePessoa);
    criaNomeBin(nomePessoa);
    arqBin = abrearq(nomePessoa,"wb");

    //reading from text file and writing data to binary file
    while(!feof(arqTxt)){

        for(int i = 0; i < TAMANHO_LIST ; i++){
            fscanf(arqTxt,"%d", &list[i]);
        }
      
        fwrite(list,sizeof(int),TAMANHO_LIST,arqBin);
    }
    //show data 
    for(int i = 0; i < TAMANHO_LIST ; i++){
        printf(" %d ",list[i]);
    }

    printf("\nArquivo gravado com sucesso !\n");

    fclose(arqTxt);
    fclose(arqBin);

    arqBin = abrearq(nomePessoa,"rb");

    //reading from binary 
    while(fread(list,sizeof(int),TAMANHO_LIST,arqBin)){
        max = achaMax(list,TAMANHO_LIST);
        printf("MAX = %d\n",max);

    }
    fclose(arqBin);

    return 0;
}

//function to open am archive and checks if it's openned properly 
FILE * abrearq(char *file,char*mode){
    FILE *a = fopen(file,mode);
    if(a == NULL){
        fprintf(stderr,"Erro ao abrir arquivo\n");
        exit(1);
    }
    return a;
}

//function to change the name of the operator and use it to define a binary file's name
void criaNomeBin(char * str){
   
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == ' '){
            str[i] = '_';
        }
        
    }
    strcat(str,".dat");
}

// function to search the greater value in a integer array 
int achaMax(int *a, int tamanho){
    int maior = 0;
    for(int i = 0; i < tamanho ; i++){
        if(a[i] > maior){
            maior = a[i];
        }
    }
    return maior;

}