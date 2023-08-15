/*Dado um vetor de n números reais, determinar os números que compõem o vetor e o número de vezes que cada um
deles ocorre no mesmo.*/

//includes
#include<stdio.h>
#include<stdlib.h>

//function prototypes
double * insereV (double * a , int size);
void imprimeV (double * a , int size);
void count_ocorrencias(double * a, int n);

//main function 
int main(void){
    //variables
    double * vetor;
    int tamanho;

    //execution
    printf("Digite o tamanho do vetor : \n");
    scanf("%d",&tamanho);

    // Dynamically allocate memory 
    vetor = (double *)malloc(tamanho*sizeof(double));
    if(vetor == NULL){
        fprintf(stderr,"erro ao alocar memória do vetor !\n");
        exit(90);
    }

    vetor = insereV(vetor,tamanho);

    printf("*****************VETOR*******************\n");
    imprimeV(vetor,tamanho);
    printf("*****************************************\n");
    count_ocorrencias(vetor, tamanho);
    
    //Deallocate memory
    free(vetor);
    vetor = NULL;
    printf("memória liberada !\n");
    return 0;
}

//function that inserts double values in each position in the array
double * insereV (double * a , int size){
    double val;
    for (int i = 0; i< size; i++){
        printf("digite o %d* valor:", i+1);
        scanf("%lf",&val);
        a[i] = val;
    }
    return a;
}

//function that prints the entire array with the assigned values 
void imprimeV (double * a , int size){
    printf("{");
    for (int i = 0; i < size; i++){
        printf("|%.1f|", a[i]);
    }
    printf("}\n");
}

void count_ocorrencias(double * a, int n) {
    int i, j, count;
    for (i = 0; i < n; i++) {
        count = 1;
        for (j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                count++;
                a[j] = 0; // mark the value as counted
            }
        }
        if (a[i] != 0) {
            printf("%.1f ocorre %d vez(es)\n", a[i], count);
        }
    }
}