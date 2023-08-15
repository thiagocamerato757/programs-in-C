/*) Implemente e teste as seguintes funções:
a. Escreva uma função que receba os valores dos lados a e b de uma caixa e sua altura h e retorne o volume da caixa.

b. Escreva uma função que receba o raio r e a altura h de um cilindro e retorne o volume do
cilindro.

c. Escreva uma função que receba os valores de a, b, h e r e, utilizando as duas funções anteriores,
retorne o volume do objeto resultado da combinacao do quadrado e do cilindro(oco)
*/
#define _CRT_SECURE_NO_WARNINGS

//since pi is a constant, we can use #define
#define PI 3.14159265359
//libraaries
#include<stdio.h>

// function prototypes
float volumeCaixa(float a, float b, float h);
float volumeCilindro(float r, float h);
float volumeObject(float a, float b, float h, float r);


//main function
int main(void) {
//variables
float ladoA;
float ladoB;
float altura;
float raio;
float VolumeObj;


//execution
printf("digite a medida do lado A !\n");
scanf("%f", &ladoA);
//in case the user inputs a wrong value
while (ladoA < 00) {
printf("valor invalido! tente novamente \n");
printf("digite a medida do lado A !\n");
scanf("%f", &ladoA);
}
printf("digite a medida do lado B !\n");
scanf("%f", &ladoB);
//in case the user inputs a wrong value
while (ladoB < 00) {
printf("valor invalido! tente novamente \n");
printf("digite a medida do lado B !\n");
scanf("%f", &ladoB);
}
printf("digite a medida da altura!\n");
scanf("%f", &altura);
//in case the user inputs a wrong value
while (altura < 00) {
    printf("valor invalido! tente novamente \n");
    printf("digite a medida da altura !\n");
    scanf("%f", &altura);
}
printf("digite a medida do raio !\n");
scanf("%f", &raio);
//in case the user inputs a wrong value
while (raio < 00) {
    printf("valor invalido! tente novamente \n");
    printf("digite a medida do raio !\n");
    scanf("%f", &raio);
}
VolumeObj = volumeObject(ladoA, ladoB, altura, raio);

    printf("volume do objeto : %f\n", VolumeObj);

return 0;
}

// function a)
float volumeCaixa(float a, float b, float h){
return a * b * h;
}
// function b)
float volumeCilindro(float r, float h) {
    return PI * (r * r) * h;
}
// function c)
float volumeObject(float a, float b, float h, float r) {
    float vCaixa = volumeCaixa(a, b, h);
    float vCilindro = volumeCilindro(r, h);
    return vCaixa - vCilindro;
}