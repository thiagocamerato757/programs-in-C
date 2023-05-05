/* Escreva o programa em que duas cadeias sejam criadas. A primeira deve ser inicializada
com “TENTATIVA”, enquanto a segunda deve ser lida do teclado, ter no máximo 20 caracteres 
e pode conter brancos. Em seguida, exiba o tamanho das duas cadeias.
O tamanho de uma cadeia deve ser obtido utilizando a função comprimento feita por você,
que recebe uma cadeia e retorna o número de caracteres dessa cadeia ( '\0' não conta).
*/

//includes 
#include<stdio.h>

//function prototypes 
int tamanhoStr(char * str);

//main function 
int main(void){
    //variables 
    char teste [] = "TENTATIVA";
    char palavra [21] = "";
    int tamanho1;
    int tamanho2;

    //execution 
    tamanho1 = tamanhoStr(teste);
    printf("O tamanho da string %s é : %d\n",teste,tamanho1);
    printf("Digite uma palavra : \n");
    scanf("%20[^\n]",palavra);
    tamanho2 = tamanhoStr(palavra);
    printf("O tamanho da string %s é : %d\n",palavra,tamanho2);

    return 0;
}

//function to count how many chars are in a string
int tamanhoStr(char * str){
    int contador = 0;
    while(*str){
        contador++;
        str += 1;
    }
    return contador;
}