/*
Escreva uma função recursiva que determine quantas vezes um dígito K 
ocorre em um número natural N. onde n é o número natural e k é o dígito(número entre 0 e 9)
que se pretende procurar em n*/

//includes
#include<stdio.h>

//function prototypes
int conta_dig(int n, int k);

//main function
int main(void){
    //variables
    int numero;
    int valor;
    int contaOcorrencia;

    //execution

    printf("Digite o número :\n");
    scanf("%d",&numero);
    printf("Digite um número(de 0 a 9) para analisarmos: \n");
    scanf("%d",&valor);
    contaOcorrencia = conta_dig(numero,valor);
    printf("O número de ocorrências do número %d em %d é : %d\n",valor,numero,contaOcorrencia);

    
    return 0;
}
//function that uses recursion to count the ocorrences of an int k in a number n
int conta_dig(int n, int k) {
    if (n == 0) {
        return 0;
    } else {
        if (n % 10 == k) {
            return 1 + conta_dig(n / 10, k);
        } else {
            return conta_dig(n / 10, k);
        }
    }
}
