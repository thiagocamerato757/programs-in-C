//includes
#include<stdio.h>
#include<stdlib.h>
#include "banco_prot.h"

Conta criaConta(void){
    Conta ct;
    ct.id = rand();//generate random number
    ct.saldo = 0.0;
    printf("Conta %d criada com sucesso !\n",ct.id);
    return ct;
}

void deposita(Conta *ct,float numb){
    ct->saldo += numb;
    return;
}

void saque(Conta *ct,float numb){
    ct->saldo -= numb;
    return;
}

void imprimeSaldo(Conta ct){
    printf("Saldo atual : %.3f",ct.saldo);
    return;
}