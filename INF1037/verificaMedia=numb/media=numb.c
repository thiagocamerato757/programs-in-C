/*Faça um programa que lê um conjunto de 10 valores inteiros e verifica se algum dos valores é igual a média dos
mesmos*/

//includes 
#include <stdio.h>

//simbolic variable
#define ARRAY_SIZE 10

//function prototypes 
void verificaMediaEnumb(int *a);

//main function 
int main(void){
    //variables 
    int val;
    int list[10];
    
    //execution 
    for (int i = 0 ; i < 10 ; i++){
        printf("digite o %d* valor :\n",i+1);
        scanf("%d",&val);
        list[i] = val ; 
    }
    
    verificaMediaEnumb(list);
    
    return 0;
}   

//function that reads a set of n integer values and checks if any of the values is equal to their average.
void verificaMediaEnumb(int *a){
    int contael = 0;
    int somael = 0;
    float media;

    for(int i = 0 ; i < ARRAY_SIZE; i++){
        somael += a[i];
        contael++;
    }
    media = (float)somael/contael;

    for(int j = 0; j < ARRAY_SIZE; j++){
        if ((float)a[j] == media){
             printf("A media %.2f foi encontrada na lista de inteiros também como %d!\n", media, a[j]);
             return;
        }
    }
    printf("A media %.2f não foi encontrada na lista de inteiros!\n", media);
    return;
}
