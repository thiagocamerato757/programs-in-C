/*Faça um programa para calcular o produto escalar de dois vetores de tamanho n*/

//includes 
#include<stdio.h>
#include<stdlib.h>

//creating a simbolic variable 
#define SIZE_VECTOR 10

//function prototypes
int * preencheVetor(int*a);
void imprimeVetor(int*a);
double produtoEscalar(int * a , int * b);

//main function 
int main(void){
    //variables
    int * vetor1;
    int * vetor2;
    double Escalar;

    //execution
    
    // Dynamically allocate memory of vector 1 
    vetor1 = (int*)malloc(SIZE_VECTOR*sizeof(int));

    if(vetor1==NULL){
        fprintf(stderr,"erro ao criar vetor de tamanho %d", SIZE_VECTOR);
        exit(1);
    }

    // Dynamically allocate memory of vector 2
    vetor2 = (int*)malloc(SIZE_VECTOR*sizeof(int));

    if(vetor2==NULL){
        fprintf(stderr,"erro ao criar vetor de tamanho %d", SIZE_VECTOR);
        exit(2);
    }

    printf("************VETOR1*************\n");
    vetor1 = preencheVetor(vetor1);

    printf("************VETOR2*************\n");
    vetor2 = preencheVetor(vetor2);

    printf("vetor 1 : ");
    imprimeVetor(vetor1);
    
    printf("vetor 2 : ");
    imprimeVetor(vetor2);

    Escalar = produtoEscalar(vetor1,vetor2);
    printf("O produto escalar entre o vetor 1 e o vetor 2 é : %.2f \n", Escalar);
    
    //deallocate all memory allocated
    free(vetor1);
    free(vetor2);
    vetor1 = NULL;
    vetor2 = NULL;
    printf("memórias liberadas !\n");

    return 0;
}

//function that inserts int values in each position in the vector
int * preencheVetor(int*a){
    int val;
    for (int i = 0; i<SIZE_VECTOR; i++){
        printf("digite o %d* valor:", i+1);
        scanf("%d",&val);
        a[i] = val;
    }
    return a;
}
//function that prints the entire vector with the assigned values 
void imprimeVetor(int*a){
    printf("{");
    for (int i = 0; i < SIZE_VECTOR; i++){
        printf("|%d|", a[i]);
    }
    printf("}\n");
}
//function that calculates the Escalar Product in between two integer vectors 
double produtoEscalar(int * a , int * b){
    double result = 0;
    for(int k = 0 ; k < SIZE_VECTOR ; k++){
        result += (a[k]*b[k]);
    }
    return result;
}