/*Implemente uma função recursiva para substituir todas as ocorrências de letras minúsculas na cadeia pela
equivalente em maiúsculo, modificando a palavra original
*/

//includes
#include<stdio.h>

//function prototypes
void maiusculo (char *str);

//main function
int main(void){
    //variables
    char palavraOriginal[100] = "";
    printf("Digite a palavra a ser modificada!\n");
    scanf("%[^\n]", palavraOriginal);
    maiusculo(palavraOriginal);
    printf("palavra modificada : %s\n",palavraOriginal);

    return 0;
}

//function that turns every low letter in upper 
void maiusculo (char *str){
    
    if((*str) >= 'a' && (*str) <= 'z'){
        *str = ((*str - 'a') + 'A');
        maiusculo(str + 1);
    }
    if(*str != '\0'){
        maiusculo(str + 1);
    }
}
