/*Escreva a função contaNaoLetras, obrigatoriamente na forma RECURSIVA, que:
 recebe uma cadeia de caracteres
 retorna o número de caracteres que não são letras (nem maiúsculas, nem minúsculas). 
A função retorna 0 no caso de cadeia vazia.
*/

//includes
#include<stdio.h>


//function prototypes
int contaNaoLetras(char * str);

//main function
int main(void){
    //variables
    char string[100] = "";
    int contagem = 0;

    //execution 
    printf("Digite uma palavra !\n");
    scanf("%[^\n]",string);
    
    contagem = contaNaoLetras(string);

    printf("A quantidade de chars que não são letras é :%d \n", contagem);
    
    
    return 0;
}

//function that uses recursion to search non letter chars 
int contaNaoLetras(char * str){
    
    if(*str == '\0'){
        return 0;
    }

    if ( (*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z')){
        return 0 + contaNaoLetras (str += 1);
    }

    else{
        return 1 + contaNaoLetras(str += 1);
    }
}
