/* Faça um programa que tendo como entrada três pontos quaisquer de um plano bidimensional (o seu
programa vai ter que ler as coordenadas do ponto A = (xA, yA), B = (xB, yB) e C = (xC, yC), ou seja, 6
valores) calcule e mostre o perímetro do triângulo formado por eles. Para implementar o seu
programa, desenvolva a função distancia(x1, y1, x2, y2) que receba como parâmetros
as coordenadas de 2 pontos (ou seja, 4 valores) e retorne a distância entre eles.
}
*/

//libraries
#include<stdio.h>

// function prototypes
int distancia(int x1, int y1, int x2, int y2);
//main function
int main(void) {
//variables
int xA;
int yA;
int xB;
int yB;
int xC;
int yC;
int perimetro;
//execution
printf("coordenada A: \n");
printf("Entre com o xA: ");
scanf("%d", &xA);
printf("Entre com o yA: ");
scanf("%d", &yA);

printf("coordenada B: \n");
printf("Entre com o xB: ");
scanf("%d", &xB);
printf("Entre com o yB: ");
scanf("%d", &yB);

printf("coordenada C: \n");
printf("Entre com o xC: ");
scanf("%d", &xC);
printf("Entre com o yC: ");
scanf("%d", &yC);



perimetro = distancia(xA, yA, xB, yB) + distancia(xB, yB, xC, yC) + distancia(xC, yC, xA, yA);
printf("O perimetro do triangulo vale %d\n",perimetro);
return 0;
}

int distancia(int x1, int y1,int x2,int y2){
return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
}