/*
Implemente uma função recursiva para verificar se uma determinada cadeia de caracteres 
é um palíndromo (i.e., se é igual lida de trás pra frente). 
Se for, retorna 1, se não for, retorna 0. A função recebe também o comprimento da cadeia.
*/

//includes
#include<stdio.h>
#include<string.h>

//function prototypes
int palindromo (char *str, int len);

//main function 
int main(void){
    //variables 
    char palavra[100] = "";
    int tamanho = 0;
    int verificaPalindromo;


    //execution
    printf("Digite a palavra :\n");
    scanf("%[^\n]",palavra);
    tamanho = strlen(palavra);
    verificaPalindromo = palindromo(palavra,tamanho);
    if(verificaPalindromo == 1){
        printf("A string é um palíndromo ! \n");
    }
    else{
        printf("A string não é um palíndromo ! \n");
    }
    
    return 0;
}

//Function to check if a string is a palindrome
int palindromo(char *str, int len) {
    if (len <= 1) {
        return 1;
    } 
    else {
        if (str[0] == ' ') {
            return palindromo(str + 1, len - 1);
        } 
        else if (str[len - 1] == ' ') {
            return palindromo(str, len - 1);
        } 
        else if (str[0] == str[len - 1]) {
            return palindromo(str + 1, len - 2);
        } 
        else {
            return 0;
        }
    }
}
