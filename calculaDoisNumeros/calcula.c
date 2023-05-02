
/* Faça uma função que retorna a soma, a diferença e o produto entre dois números. Os resultados devem retornar por
parâmetros passados por referência.*/


//includes
#include <stdio.h>

//function prototypes
void calcular(int a, int b, int *c, int *d, int *e);

//main function 
int main() {
    //variables 
    int num1;
    int num2;
    int soma;
    int dif;
    int prod;

    //execution
    printf("Digite dois numeros: ");
    scanf("%d %d", &num1, &num2);

    calcular(num1, num2, &soma, &dif, &prod);

    printf("Soma:%d\n", soma);
    printf("Diferenca:%d\n", dif);
    printf("Produto:%d\n", prod);

    return 0;
}
//function that returns the sum, difference, and product between two numbers and The results are returned through parameters passed by reference
void calcular(int a, int b, int *c, int *d, int *e) {
    *c = a + b;
    *d = a - b;
    *e = a * b;
    return;
}