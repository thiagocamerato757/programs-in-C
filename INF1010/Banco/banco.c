//includes
#include<stdio.h>
#include"banco_prot.h"

//main function
int main(void){
    //variables
    Conta *newConta;
    float dinheiro;
    // execution
    *newConta = criaConta();
    printf("digite a quantidade que deseja depositar\n");
    scanf("%f",&dinheiro);
    deposita(newConta,dinheiro);
    printf("Digite a quantidade que deseja retirar\n");
    scanf("%f",&dinheiro);
    saque(newConta,dinheiro);
    imprimeSaldo(*newConta);
    return 0;
}