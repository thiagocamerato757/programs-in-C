//includes
#include<stdio.h>
#include <stdlib.h>

//structed data
struct termo
{
    int coef;
    int grau;
};
typedef struct termo Termo;

//function prototypes
Termo* criaVetorSoma(Termo* vetor1, int tamanho1, Termo* vetor2, int tamanho2, int* tamanhoResultado);


int main(void){
    //variables
    Termo polinomio1[4] = {{5, 6}, {8, 3}, {1, 2}, {7, 0}};
    Termo polinomio2[2] = {{2, 4}, {7, 2}};
    int tamanhoResultado;
    Termo* resultado;


    //execution
    resultado = criaVetorSoma(polinomio1, 4, polinomio2, 2, &tamanhoResultado);
    printf("Polinômio resultante:\n");
    for (int i = 0; i < tamanhoResultado; i++){
        printf("%dx^%d ", resultado[i].coef, resultado[i].grau);
        if (i < tamanhoResultado - 1){
            printf("+ ");
        }
    }
    printf("\n");
    
    free(resultado);
    
    return 0;
}

//function to sum two polynoms of n sizes 
Termo* criaVetorSoma(Termo* vetor1, int tamanho1, Termo* vetor2, int tamanho2, int* tamanhoResultado){
    int i = 0; 
    int j = 0;
    int k = 0;
    int tamanho = tamanho1 + tamanho2;
    
    Termo* resultado = (Termo*)malloc(tamanho * sizeof(Termo));
    if(resultado == NULL){
        fprintf(stderr,"Erro ao alocar memória\n");
        exit(1);
    }
    
    while (i < tamanho1 && j < tamanho2){
        if (vetor1[i].grau > vetor2[j].grau){
            resultado[k] = vetor1[i];
            i++;
        }
        else if (vetor1[i].grau < vetor2[j].grau){
            resultado[k] = vetor2[j];
            j++;
        }
        else{
            resultado[k].grau = vetor1[i].grau;
            resultado[k].coef = vetor1[i].coef + vetor2[j].coef;
            i++;
            j++;
        }
        
        k++;
    }
    
    while (i < tamanho1){
        resultado[k] = vetor1[i];
        i++;
        k++;
    }
    
    while (j < tamanho2){
        resultado[k] = vetor2[j];
        j++;
        k++;
    }
    
    *tamanhoResultado = k;
    return resultado;
}
