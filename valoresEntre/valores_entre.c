

//includes 
#include<stdio.h>
#include<stdlib.h>

//function prototypes
void printArray(int *a, int n);
int * valores_entre(int *v ,int n , int min, int max, int *qtd);

//main function 
int main(void){
    int valorMin;
    int valorMax;
    int vetorInt[10] = {1,3,6,10,4,50,-10,30,41,32};//random vector to test function 
    int *vetorResposta;
    int quantidade = 0;

    printArray(vetorInt,10);
    printf("Digite um número inteiro mínimo : \n");
    scanf("%d",&valorMin);
    printf("Digite um número inteiro máximo : \n");
    scanf("%d",&valorMax);
    vetorResposta = valores_entre(vetorInt,10,valorMin,valorMax,&quantidade);
    if(vetorResposta == NULL){
        printf("Não foi possível realizar a operação com esses dois números\n");
    }
    else{
        printf("Quantidade de valores alocados dinamicamente: %d\n", quantidade);
        printArray(vetorResposta,quantidade);
        //Deallocate memory
        free(vetorResposta);
    }
    return 0;

}

void printArray(int *a, int n){
    printf("[ ");
    for(int i = 0; i < n; i++){
        printf("%d ",a[i]);
    }
    printf("]\n");
}

int * valores_entre(int *v ,int n , int min, int max, int *qtd){
    for(int i = 0; i < n ; i++){
        if(v[i] > min && v[i] < max){
            (*qtd) += 1;
        }
    }

    int *valoresEntreMINMAX;
    valoresEntreMINMAX = (int *)malloc((*qtd)*sizeof(int));

    if(valoresEntreMINMAX == NULL){
        return valoresEntreMINMAX;
    }
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] > min && v[i] < max) {
            valoresEntreMINMAX[index] = v[i];
            index++;
        }
    }
    return valoresEntreMINMAX;  
    
}