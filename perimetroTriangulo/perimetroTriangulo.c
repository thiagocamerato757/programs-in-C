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
double distancia(double x1, double y1, double x2, double y2);

//main function
int main(void) {
//variables
double xA;
double yA;
double xB;
double yB;
double xC;
double yC;
double perimetro;
//execution
printf("coordenada A: \n");
printf("Entre com o xA: ");
scanf("%lf", &xA);
printf("Entre com o yA: ");
scanf("%lf", &yA);

printf("coordenada B: \n");
printf("Entre com o xB: ");
scanf("%lf", &xB);
printf("Entre com o yB: ");
scanf("%lf", &yB);

printf("coordenada C: \n");
printf("Entre com o xC: ");
scanf("%lf", &xC);
printf("Entre com o yC: ");
scanf("%lf", &yC);



perimetro = distancia(xA, yA, xB, yB) + distancia(xB, yB, xC, yC) + distancia(xC, yC, xA, yA);
printf("O perimetro do triangulo vale %.2f\n",perimetro);
return 0;
}
// function to calculate the distance in between a particule
double distancia(double x1, double y1, double x2, double y2){
    double result;
    double conta;
    conta = (x1 - x2) * (x1 - x2) + ((y1 - y2) * (y1 - y2));
    result = sqrt(conta);
return result ;
}