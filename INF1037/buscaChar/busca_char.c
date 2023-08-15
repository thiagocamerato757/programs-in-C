/*Escreva uma função recursiva para procurar um caractere em uma cadeia de caracteres.
Caso o caractere seja encontrado, a função deve retornar 1, caso contrário, deve retornar 0.  
*/

//includes
#include<stdio.h>

//function prototypes
int busca(char *str, char c);

//main function 
int main(void){
    //variables
    char senteca[100]="";
    char charselect;
    int result = 0;

    //execution 
    printf("Digite a palavra !\n");
    scanf("%[^\n]",senteca);
    printf("Digite o char que deseja achar\n");
    scanf("\n%c",&charselect);
    result = busca(senteca,charselect);
    if(result == 1){
        printf("character encontrado\n");
    }
    else{
        printf("character não encontrado\n");
    }
    



    return 0;
}

//function that uses recursion to search for a char
int busca(char *str, char c){
    if(*str == '\0'){
        return 0;
    }
    else{
        if(*str == c){
            return 1;
        }
        else{
            return busca(str + 1, c); 
        }
        
    }
}