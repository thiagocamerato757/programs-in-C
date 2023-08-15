/*Escreva a função contaB, que recebe uma cadeia e retorna (devolve) 2 valores:
o número de ´b´s  e o número de ´B´s.*/

//includes 
#include<stdio.h>


//function prototypes 
int contaB(char *a,int *b);



//main function 
int main(void){
    //variables 
    char palavra[100];
    int conta_b = 0;
    int conta_B = 0;

    //execution
    printf("Digite alguma palavra com b ou B\n");
    scanf("%[^\n]",palavra);
    conta_B = contaB(palavra,&conta_b);
    printf("quantidade de 'B's : %d\n",conta_B);
    printf("quantidade de 'b's : %d\n",conta_b);

    return 0;
}
//function that counts de ocurrences of 'B' and 'b'
int contaB(char *a,int *b){
    int conta = 0;
    while(*a){
        if(*a == 'b'){
            (*b)+=1;
        }
        else if(*a == 'B'){
            conta++;
        }
        a+=1;
    }
    return conta;
}