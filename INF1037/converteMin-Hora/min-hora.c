/*Desenvolva um programa que leia a quantidade total de segundos e converta para Horas, Minutos e Segundos.
Imprima o resultado da conversão no formato HH:MM:SS. Para isso, utilize a função com protótipo  
void converteHora (int total segundos, int *hora, int *min, int *seg).
*/

//includes
#include<stdio.h>

//function prototypes
void converteHora (int a , int *b, int *c, int *d);


//main function
int main(void){
    //variables
    int totalS;
    int hora;
    int min;
    int seg;

    //execution
    printf("Digite o total de segundos :\n");
    scanf("%d",&totalS);
    converteHora(totalS,&hora,&min,&seg);
    
    
    return 0;
}
// function that reads the total amount of seconds and converts it to Hours, Minutes, and Seconds.
// and prints the conversion result in the format HH:MM:SS.
void converteHora (int a , int *b, int *c, int *d){
    double totalMin = a / 60.0;
    *b = (int) (totalMin / 60.0);
    *c = (int) (totalMin - (*b * 60.0));
    *d = a % 60;

    printf("hora vale : %02d h : %02d m : %02d s", *b, *c , *d);
}