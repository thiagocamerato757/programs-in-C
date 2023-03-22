/* Faça um programa que tendo como entrada três pontos quaisquer de um plano bidimensional (o seu
programa vai ter que ler as coordenadas do ponto A = (xA, yA), B = (xB, yB) e C = (xC, yC), ou seja, 6
valores) calcule e mostre o perímetro do triângulo formado por eles. Para implementar o seu
programa, desenvolva a função distancia(x1, y1, x2, y2) que receba como parâmetros
as coordenadas de 2 pontos (ou seja, 4 valores) e retorne a distância entre eles.
}
*/

//libraries
#include<stdio.h>
#include<math.h>

// function prototypes
int distancia(float x1, float y1, float x2, float y2);
//main function
int main(void) {
//variables
float xA;
float yA;
float xB;
float yB;
float xC;
float yC;
float perimetro;
//execution
printf("coordenada A: \n");
printf("Entre com o xA: ");
scanf("%f", &xA);
printf("Entre com o yA: ");
scanf("%f", &yA);

printf("coordenada B: \n");
printf("Entre com o xB: ");
scanf("%f", &xB);
printf("Entre com o yB: ");
scanf("%f", &yB);

printf("coordenada C: \n");
printf("Entre com o xC: ");
scanf("%f", &xC);
printf("Entre com o yC: ");
scanf("%f", &yC);



perimetro = distancia(xA, yA, xB, yB) + distancia(xB, yB, xC, yC) + distancia(xC, yC, xA, yA);
printf("O perimetro do triangulo vale %f\n",perimetro);
return 0;
}

int distancia(float x1, float y1,float x2,float y2){
    int result;
    result = sqrtf(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
return result;
}