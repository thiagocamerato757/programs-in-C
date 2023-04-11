
//includes 
#include<stdio.h>
#include"meu_header.h"

//creating simbolic variables 
#define TRUE 1
#define FALSE 0


//main function
int main(void){
  
    //variables 
    int linhas;
    int colunas;
    int ** matriz2D;
    int constante;
    int quadrada;
    int diagonal;
    char boolean;
    
    //execution 
    printf("Digite o número de linhas da Matriz 2D :\n");
    scanf("%d",&linhas);
    printf("Digite o número de colunas da Matriz 2D : \n");
    scanf("%d",&colunas);
   
    matriz2D = criaMatriz(linhas,colunas);

    printf("Matrix %d X %d criada :\n\n", linhas,colunas);
    imprimeMatriz2D(matriz2D, linhas, colunas);
    
    printf("\nDigite o valor da constante !\n");
    scanf("%d",&constante);
    printf("Matrix %d X %d com constante %d criada :\n\n",linhas,colunas,constante);
    quadrada = alteraMatriz2D(matriz2D,constante,linhas,colunas);

    diagonal = verificaDiagonalidade(matriz2D,linhas,colunas,quadrada);
  
    //using the ternary operator to use in the printf() function 
    boolean = diagonal == TRUE ? 'S' : 'N';

    printf("\nA matrix é diagonal ?  %c \n\n",boolean);
    
    liberaMemoria (matriz2D, linhas);
  
    return 0;
}

