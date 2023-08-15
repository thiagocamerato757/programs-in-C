/* Crie as funções necessárias para o funcionamento correto do programa abaixo. Não altere o código
apresentado, apenas inclua as funções que estão faltando. Antes de implementar as funções, leia o
texto do programa e infira o seu funcionamento.

int main(void) {

int n1;
int n2;
int n3;
int aux;
int nPares;

printf("Entre com o 1o numero: ");
scanf("%d", &n1);
printf("Entre com o 2o numero: ");
scanf("%d", &n2);
printf("Entre com o 3o numero: ");
scanf("%d", &n3);
aux = maior(n1, n2);
printf("O maior numero lido vale %d\n" , maior(aux, n3));
printf("O valor medio lido vale %d\n" , media(n1, n2, n3));
// A partir daqui não é mais para os fracos
nPares = par(n1) + par(n2) + par(n3);
printf("A quantidade de numeros pares lida vale %d" , nPares);
return 0;
}
*/


//libraries
#include<stdio.h>

// function prototypes
int maior(int a, int b);
int media(int a, int b, int c);
int par(int x);
//main function
int main(void) {
//variables
int n1;
int n2;
int n3;
int aux;
int nPares;
//execution
printf("Entre com o 1o numero: ");
scanf("%d", &n1);
printf("Entre com o 2o numero: ");
scanf("%d", &n2);
printf("Entre com o 3o numero: ");
scanf("%d", &n3);
aux = maior(n1, n2);
printf("O maior numero lido vale %d\n", maior(aux, n3));
printf("O valor medio lido vale %d\n", media(n1, n2, n3));

nPares = par(n1) + par(n2) + par(n3);
printf("A quantidade de numeros pares lida vale %d\n", nPares);
return 0;
}

int maior(int a, int b) {
if (a > b) {
return a;
}
else return b;
}
int media(int a, int b, int c) {
return (a + b + c) / 3;
}
int par(int x) {
if (x % 2 == 0) {
return 1;
}
else return 0;
}