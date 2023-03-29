/*Escreva uma função que receba o número de dias de duração de um evento e exiba no monitor a
duração expressa em números de semanas e número de dias.
*/

//libraries
#include<stdio.h>

// function prototypes
void mostraTempo(int c);



//main function
int main(void) {
//variables
int diasDecorridos;


//execution
printf("digite os dias decorridos do evento !\n");
scanf("%d", &diasDecorridos);
//in case the user inputs a wrong value
while (diasDecorridos < 00) {
printf("valor invalido! tente novamente \n");
printf("digite os dias decorridos do evento !\n");
scanf("%d", &diasDecorridos);
}
mostraTempo(diasDecorridos);


return 0;
}

// function to show the convertion of days in weeks and days in days
void  mostraTempo(int c) {
    printf("O evento durou %d semana(s) e %d dia(s).\n\n",c/7, c%7);
}
