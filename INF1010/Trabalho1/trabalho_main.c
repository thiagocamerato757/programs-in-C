#include "trabalho_aux.h"
#include<stdio.h>
#include<stdlib.h>

int main(void) {
    printf("-------------------------ITEM 1-------------------------\n");
    const char* expressao1 = "3 2 7 * + 1 -";
    const char* expressao2 = "2 3 4 1 + * -";
    const char* expressao3 = "5 1 2 + 4 * + 3 -";
    const char* expressao4 = "7 5 6 2 / 8 * + 3 + *";
    const char* expressao5 = "2 1 / 4 2 * + 6 5 - 8 2 / + +";

    int resultado1 = calculatePostfix(expressao1);
    int resultado2 = calculatePostfix(expressao2);
    int resultado3 = calculatePostfix(expressao3);
    int resultado4 = calculatePostfix(expressao4);
    int resultado5 = calculatePostfix(expressao5);

    printf("Resultado da expressao "" %s "": %d\n", expressao1, resultado1);
    printf("Resultado da expressao "" %s "": %d\n", expressao2, resultado2);
    printf("Resultado da expressao "" %s "": %d\n", expressao3, resultado3);
    printf("Resultado da expressao "" %s "": %d\n", expressao4, resultado4);
    printf("Resultado da expressao "" %s "": %d\n", expressao5, resultado5);

    printf("-------------------------ITEM 2-------------------------\n");


    return 0;
}