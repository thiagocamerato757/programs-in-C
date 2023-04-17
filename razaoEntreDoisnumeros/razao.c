/*Faça uma função que retorna a razão entre dois números. A função deve retornar pelo comando return o valor 1 se a
operação foi possível e o valor 0 se a operação não foi possível (divisão por zero, por exemplo). O resultado da divisão
deve retornar por um parâmetro por referência
*/

//includes
#include<stdio.h>

//function prototypes 
int calculaRazao(int a , int b , float *c);

//main function 
int main(void){
    //variables
    int numb1;
    int numb2;
    float razao;
    int check;

    //execution 
    printf("Digite dois numeros: ");
    scanf("%d %d", &numb1, &numb2);

    check = calculaRazao(numb1,numb2,&razao);
    
    if (check == 0){
        printf("Operação de divisão impossível !");
    }
    else{
        printf ("A razao entre %d e %d é : %.2f",numb1,numb2,razao);
    }
    
    
    
    return 0;
}
//function that returns the ratio between two numbers. The function returns a value of 1 by using the return statement 
//if the operation was successful, and 0 if the operation was not possible (for example, division by zero). 
//The result of the division are returned through a parameter by reference.
int calculaRazao(int a , int b , float *c){
    if (b == 0){
        return 0;
    }

    *c = a/ (float)b;
    return 1;
}