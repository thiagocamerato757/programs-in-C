/*Escreva uma função que receba o código de um produto (valor inteiro com 4 algarismos) e, utilizando
a função calcula_percent, criada em exercício anterior, retorne o valor total a pagar pelo produto. O
valor básico do produto e percentual de desconto são obtidos do código do produto de acordo com a
seguinte regra:
• Código do produto: XXYY
• Preço básico: XX * 15,00 + YY
• Percentual de desconto: YY
*/

//libaries
#include<stdio.h>


//function prototypes

float calcula_percent(float valor, int percent);

//main function
int main(void) {
//variables

int codigo;
int valYY;
float valXX;
float valorBasico;
float valorPercent;
float valorFinal;

// execution
printf("digite o codigo de 4 numeros!\n");
scanf("%d", &codigo);

// in case the user inputs a wrong code
if (codigo < 0000 || codigo > 9999) {
    printf("codigo invalido !");
    return -1;
}


valYY = (codigo % 100);
valXX = (codigo / 100);
valorBasico = (int)valXX * 15.00 + valYY;
valorPercent = calcula_percent(valorBasico, valYY);
valorFinal = valorBasico - valorPercent;

printf("codigo do produto : %d\n", codigo);

printf("Preco basico: %.0f * 15,00 + %d  = %.2f    Percentual de desconto: %d %% Total a pagar: %.2f\n", valXX, valYY, valorBasico,valYY,valorFinal);



return 0;
}


float calcula_percent(float valor, int percent) {
    float resultado;
    resultado = valor * ((float)percent / 100);
    return resultado;
}