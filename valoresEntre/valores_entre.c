/*Crie um programa para manipular vetores. O seu programa deve implementar uma função que receba um vetor de inteiros V e retorne um outro vetor de inteiros alocado dinamicamente com todos os valores de V que estejam entre o valor mínimo e máximo (que também são passados como parâmetro para a função).
A função deve obedecer ao seguinte protótipo:
int* valores_ entre (int *v, int n, int min, int max, int 'qtd)
A função recebe:
 v: vetor de números inteiros;
 n: a quantidade de elementos do vetor v;
 min: valor mínimo a ser buscado;
 max: valor máximo a ser buscado;
A função deve:
 Verificar a quantidade de elementos do vetor que sejam maiores do que min e menores que max;
 Caso a quantidade seja maior do que O (zero), alocar dinamicamente uma área do exato tamanho necessário para armazenar os valores
 Copia os elementos do vetor que sejam maiores do que min e menores que max
para a área alocada dinamicamente.
A função retorna:
 O endereço da área alocada dinamicamente, preenchida com os números maiores do que min e menores que max, ou NULL, caso essa relação de números não tenha sido criada;
 A quantidade de números carregados na área alocada dinamicamente, através do parâmetro qtd.
Em seguida, crie a função principal do programa para inicializar um vetor de inteiros, exibir esses valores na tela e pedir para o usuário digitar o valor mínimo e máximo a ser buscado. Em seguida o programa deverá chamar a função valores entre e exibir na tela os valores resultantes. Lembre-se de exibir uma mensagem de erro caso nenhum valor seja encontrado.
Não se esqueça de liberar a memória alocada dinamicamente
*/

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
//function to print an array 
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
    // function to return a dynamically allocated of the integers between Min & Max
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