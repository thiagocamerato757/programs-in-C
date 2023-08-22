//includes
#include <stdio.h>
#include <stdlib.h>

//function prototypes
int fibonacciRecursivo(int n);
int* calcularFibonacciRecursivo(int n);

//main function
int main(void) {
    int n;

    printf("Digite o valor de n: ");
    scanf("%d", &n);

    int* fibonacci = calcularFibonacciRecursivo(n);

    if (fibonacci) {
        printf("%d\n",fibonacci[n]);
        free(fibonacci);
    } 
    else {
        printf("Valor inválido de n ou erro de alocação de memória.\n");
    }

    return 0;
}

//function to recursevilly gives a number from Fibonacci sequence
int fibonacciRecursivo(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}
//function to store each Fibonacci number 
int* calcularFibonacciRecursivo(int n) {
    if (n <= 0) return NULL;

    int* fibonacci = (int*)malloc(n * sizeof(int));
    if (!fibonacci) return NULL;

    for (int i = 0; i <= n; i++) {
        fibonacci[i] = fibonacciRecursivo(i);
    }

    return fibonacci;
}