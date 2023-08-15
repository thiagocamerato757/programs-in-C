/*Implemente e teste as seguintes funções:
a. Escreva uma função chamada soma_dig que receba como parâmetro um número inteiro de
2 algarismos e retorne a soma dos algarismos desse número.
b. Escreva uma função chamada geraSenha que receba três inteiros representando dia, mês e
ano de nascimento de um aluno e, utilizando a função soma_dig, exiba a senha do aluno,
string gerada a partir da concatenação da soma dos dígitos do dia com a soma dos dígitos do
mês com a soma dos dois últimos dígitos do ano.
*/

//libraaries
#include<stdio.h>

// function prototypes
int soma_dig(int a);
void geraSenha(int c, int d, int e);



//main function
int main(void) {
//variables
int dia;
int mes;
int ano;

//execution
printf("digite dia de seu nascimento!\n");
scanf("%d", &dia);
//in case the user inputs a wrong value
while (dia < 01 || dia > 31) {
    printf("valor invalido! tente novamente \n");
    printf("digite dia de seu nascimento!\n");
    scanf("%d", &dia);
}
printf("digite mes de seu nascimento!\n");
scanf("%d", &mes);
//in case the user inputs a wrong value
while (mes < 01 || mes > 12) {
    printf("valor invalido! tente novamente \n");
    printf("digite mes de seu nascimento!\n");
    scanf("%d", &mes);
}
printf("digite ano de seu nascimento!\n");
scanf("%d", &ano);
//in case the user inputs a wrong value
while (ano < 1900) {
    printf("valor invalido! tente novamente \n");
    printf("digite ano de seu nascimento!\n");
    scanf("%d", &ano);
}
geraSenha(dia, mes, ano);


return 0;
}


// function in a)
int soma_dig(int a) {
    int result;
    result = (a / 10) + (a % 10);
    return result;
}
// function in b)
void geraSenha(int c, int d, int e) {
    printf("senha gerada : %d%d%d\n", soma_dig(c),soma_dig(d),soma_dig(e % 100));

}