/*Escreva uma  unção chamada erro_percentual que receba o valor exato de um número e seu valor
aproximado e retorne o erro percentual. A função deve, obrigatoriamente, utilizar as funções  erro_absoluto
(diferença absoluta entre o valor exato deum número (𝑥) e o seu valor aproximado (𝑥̅) )erro_relativo (dividido pelo valor aproximado).
O erro percentual é a representação percentual do erro relativo.

Não coloque as duas funções no mesmo arquivo. Crie um arquivo com os protótipos.
*/


//libraries
#include<stdio.h>
#include<math.h>

// function prototypes
float erro_absoluto(int a, float b);
float erro_relativo(int a, float b);
float erro_percentual(int a, float b);

//main function
int main(void) {
//variables
int numero;
float aprox;
float erroPercent;


//execution
printf("digite o numero !\n");
scanf("%d", &numero);

printf("digite o valor aproximado ao numero anterior !\n");
scanf("%f", &aprox);

erroPercent = erro_percentual(numero, aprox);
printf("Erro percentual : %f %%\n", erroPercent);

return 0;
}
// function to return the absolute error in between two numbers
float erro_absoluto(int a, float b) {
float result;
// the fabs() function is used to get the absolute value of a float number
    result = fabs(a - b);
    return result;
}
// function to return the relative error in between two numbers using the absolute error function
float erro_relativo(int a, float b) {
    float result;
    result = (erro_absoluto(a, b) / b);
    return result;
}
// function to return the percentual error in between two numbers using the relative error function
float erro_percentual(int a, float b) {
    float result;
    result = erro_relativo(a, b) * (100);
    return result;
}