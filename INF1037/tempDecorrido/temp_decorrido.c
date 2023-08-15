/*: faça um programa que leia horário (hora e minuto) do início e do término de um evento e
informe a sua duração. Para isso:
a. faça uma função para converter hora e minuto para minutos;
b. faça uma função que receba um tempo em minutos e exiba no formato HH:MM.
*/

//libraries
#include<stdio.h>

// function prototypes
int horasConverte(int a,char b);
void mostraHora(int c);



//main function
int main(void) {
//variables
int hora1;
int minuto1;
int hora2;
int minuto2;
int totalMin1;
int totalMin2;
int tempDecorrido;


//execution
printf("Hora do inicio do evento:\n");
printf("digite a hora !\n");
scanf("%d", &hora1);
//in case the user inputs a wrong value
while (hora1 < 00 || hora1 > 23) {
printf("valor invalido! tente novamente \n");
printf("digite a hora !\n");
scanf("%d", &hora1);
}
printf("digite os minutos !\n");
scanf("%d", &minuto1);
//in case the user inputs a wrong value
while (minuto1 < 00 || minuto1 > 59) {
printf("valor invalido! tente novamente \n");
printf("digite os minutos !\n");
scanf("%d", &minuto1);
}

printf("Hora do termino do evento:\n");
printf("digite a hora !\n");
scanf("%d", &hora2);
//in case the user inputs a wrong value
while (hora2 < 00 || hora2 > 23) {
printf("valor invalido! tente novamente \n");
printf("digite a hora !\n");
scanf("%d", &hora2);
}
printf("digite os minutos !\n");
scanf("%d", &minuto2);
//in case the user inputs a wrong value
while (minuto2 < 00 || minuto2 > 59) {
printf("valor invalido! tente novamente \n");
printf("digite os minutos !\n");
scanf("%d", &minuto2);
}


totalMin1 = horasConverte(hora1, 'h') + horasConverte(minuto1, 'm');
totalMin2 = horasConverte(hora2, 'h') + horasConverte(minuto2, 'm');
tempDecorrido = totalMin2 - totalMin1;

printf("hora de inicio: ");
mostraHora(totalMin1);
printf("hora de termino: ");
mostraHora(totalMin2);
printf("hora decorrida: ");
mostraHora(tempDecorrido);
return 0;
}


// function in a)
int horasConverte(int a,char b) {
    int result;
    if (b == 'h' || b == 'H') {
        result = (a * 60);
        return result;
    }
    else if(b == 'm' || b == 'M'){
        result = a;
        return result;
    }
}
// function in b)
void mostraHora(int c) {
printf("%d:%d\n\n",c/60, c%60);
}

