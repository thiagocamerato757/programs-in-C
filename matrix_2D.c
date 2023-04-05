//includes 
#include<stdio.h>
#include<stdlib.h>

//creating simbolic variables 
#define TRUE 1
#define FALSE 0

//functions prototypes
int ** criaMatriz(int a, int b);
void imprimeMatriz2D(int ** c,int a ,int b);
void liberaMemoria (int ** c, int a);
int alteraMatriz2D(int **c, int q, int a , int b);
int verificaDiagonalidade(int** c, int a, int b, int bool );


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
   
    matriz2D = criaMatrix(linhas,colunas);

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

// function to create a dinamic allocated Array with zeros
int ** criaMatriz(int a, int b){
    
    // Dynamically allocate memory 
    int ** M = (int **)malloc(a * sizeof(int *));
    
    if (M == NULL){
        fprintf(stderr,"sem memória !\n");
        exit(0);
    }

    for (int i = 0; i < a ; i++){

        M[i] = (int*)malloc(b * sizeof(int));
        
        if (M[i]==NULL){
            fprintf(stderr,"sem memória !\n");
            exit(0);
        }

    }

    // assign values to the allocated memory
    for (int s = 0 ; s < a ; s++){
        
        for (int t = 0; t < b ; t++){
            
            M[s][t] = 0;
        }
    }

    return M;

    }
//function to print the Array 
void imprimeMatriz2D(int ** c, int a,int b){

    for (int i = 0; i < a;i++){

        for( int j = 0; j < b ; j++){

            printf("|%2.1d ",c[i][j]);
        }

        printf("|\n");
    }
}
//function to deallocate all memory of the Array
void liberaMemoria (int ** c, int a ){

    for (int i = 0; i < a;i++){
        free(c[i]);
    }
    free(c);
    printf("Memória liberada !\n");

}

//function to change the Array with a value in order to try turn the array into a diagonal Array at the same time 
// verifies if the array is a quadric Array and return TRUE or FALSE 
int alteraMatrix2D(int **c, int q, int a , int b){

    for (int i = 0 ; i < a ; i++){
        for (int j = 0; j < b; j++){
            if(i == j){
                c[i][j] =  q ;
            }    
        }
    }

    if(a == b){
        imprimeMatrix2D(c, a, b);
        return TRUE;
    }

    else {
        imprimeMatrix2D(c, a, b);
        return FALSE;
    }      
}

//function to see if the Array is a diagonal Array
int verificaDiagonalidade(int** c, int a, int b, int bool ){
    int diagonal = TRUE;
    if (bool == FALSE) {

        return FALSE;
    }
    for (int i = 0; i < a ; i++){
        for (int j = 0 ; j < b ; j++ ){
            if(i != j && c[i][j] != 0){
                diagonal =  FALSE;
                return diagonal;
            }
    }

   }
    return diagonal;
}
