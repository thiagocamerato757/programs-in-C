/*Calcule o valor de um polinômio p(x) = a_0 + a_1*x +...+ a_n*(x^n) para k valores de x diferentes. São dados n (grau do
polinômio), um vetor a = {a0, a1, ..., an} (coeficientes reais do polinômio) e um vetor k = {x0, x1, ..., xk} 
(os valores de x para os quais se deseja calcular o polinômio). Armazene a resposta 
num vetor p ={p(x0), p(x1), ..., p(xk)} */

//includes
#include<stdio.h>
#include<stdlib.h>

//function prototypes 
double * insere (double * a , int size);
void imprimeVetor(double * a , int size);
double calculaPolinomio(double * a , double b, int g );

//main function
int main(void){
    //variables
    int grau;
    int kvalores;
    double * coeficientes;
    double * k;
    double * resposta;

    //execution
    printf("Digite o número de valores para x !\n");
    scanf("%d",&kvalores);
    printf("Digite o grau do polinômio!\n");
    scanf("%d",&grau); 

    // Dynamically allocate memory 
    k = (double *)malloc(kvalores * sizeof(double));
    if(k == NULL){
        fprintf(stderr,"Erro ao alocar memória !\n");
        exit(1);
    }

    coeficientes = (double *)malloc((grau+1) * sizeof(double)); 
    if(coeficientes == NULL){
        fprintf(stderr,"Erro ao alocar memória !\n");
        exit(2);
    }

    resposta = (double *)malloc(kvalores * sizeof(double));
    if(resposta == NULL){
        fprintf(stderr,"Erro ao alocar memória !\n");
        exit(3);
    }

    //inserting values
    printf("***************VALORES DE X******************\n");
    k = insere (k ,kvalores);
    printf("**************COEFICIENTES DE X**************\n");  
    coeficientes = insere (coeficientes ,grau+1);
    printf("*****VETOR RESPOSTA PARA %d VALORES DE X*****\n\n" , kvalores); 
    
    for(int f = 0; f < kvalores; f++){
        resposta[f] = calculaPolinomio(coeficientes , k[f] , grau);  
    }

    //printing 
    imprimeVetor(resposta, kvalores);
    
    //Deallocate memory
    free(k);
    free(coeficientes);
    free(resposta);
    k = NULL;
    coeficientes = NULL;
    resposta = NULL ;
    printf("\nMemórias liberadas \n");

    return 0;
}

//function that inserts double values in each position in the array
double * insere (double * a , int size){
    double val;
    for (int i = 0; i< size; i++){
        printf("digite o %d* valor:", i+1);
        scanf("%lf",&val);
        a[i] = val;
    }
    return a;
}

//function that prints the entire array with the assigned values 
void imprimeVetor(double * a , int size){
    printf("{");
    for (int i = 0; i < size; i++){
        printf("|%.2f|", a[i]);
    }
    printf("}\n");
}


//funcion that calculates the result of a polynomial funtion of type : p(x) = a_0 + a_1*x +...+ a_n*(x^n) 
double calculaPolinomio(double * a , double b, int g ){  
    double result = 0;
    double temp = 1;
    for (int i = 0 ; i <= g ; i ++ ){  
        result +=  a[i] * temp;
        temp *= b;
    }
    return result;
}