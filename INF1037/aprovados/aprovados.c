/*Escreva a função criaAprovados que:
‐ recebe o número de alunos de uma turma, um vetor (de inteiros) com as matrículas dos alunos da turma, um vetor
(de float) com as notas (vnota[k] é a nota do aluno com inscrição vinsc[k]) e o endereço de uma variável inteira
onde deve ser devolvida a quantidade de alunos aprovados  
‐ retorna um novo vetor de inteiros, criado com alocação dinâmica com o tamanho exato necessário, apenas com as
matrículas dos alunos aprovados, ou seja, aquele que têm nota >=5.0. A função também devolve na variável cujo
endereço foi recebido como parâmetro a quantidade de elementos do novo vetor (ou seja, de aprovados). Caso não
exista nenhum aluno aprovado ou não seja possível alocar espaço para o novo vetor, a função retorna NULL.
Faça uma função main para testar a função criada.
OBSERVAÇÃO: Não esqueça de que na main() deve ser feita a chamada desta função e as respostas exibidas. Assim se
não ocorreu nenhum problema, devem ser exibidos: a quantidade de elementos e os valores dos elementos do vetor
retornado. Caso tenha ocorrido algum problema, deve ser exibida uma das mensagens abaixo (a mais apropriada):  
• “Nenhum aluno aprovado”, caso nenhum aluno tenha nota >= 5.0.  
• “Nao foi possivel alocar espaco", caso não seja possível alocar memória para o novo vetor de aprovados.*/



//includes 
#include<stdio.h>
#include<stdlib.h>

//function prototypes 
void insert (int*a, float *b, int c);
void printV(int * a , int b);
int * criaAprovados(int * a , float * b , int c , int * d);

//main function 
int main (void){
    //variables 
    int nAlunos;
    int * matricula;
    float * notas;
    int qtdAprovados;
    int * alunosP;


    //execution
    printf("Digite a quantidade de alunos \n");
    scanf("%d",&nAlunos);

    //Dynamically allocate memory 
    matricula = (int *)malloc(nAlunos*sizeof(int));
    if (matricula == NULL){
        fprintf(stderr,"Erro ao alocar a memória !\n");
        exit(-5);
    }

    notas = (float *)malloc(nAlunos*sizeof(float));
    if (notas == NULL){
        fprintf(stderr,"Erro ao alocar a memória !\n");
        exit(-4);
    }

    insert(matricula,notas,nAlunos);
    alunosP = criaAprovados(matricula,notas,nAlunos,&qtdAprovados);

    if(alunosP == NULL){
        printf("Nenhum aluno foi aprovado ! \n");
    }
    else{
        printV(alunosP,qtdAprovados);
    }
    //Deallocate memory
    free(matricula);
    free(notas);
    free(alunosP);
    matricula = NULL;
    notas = NULL;
    alunosP = NULL;
    
    return 0;
}

void insert (int*a, float *b, int c){
    for (int i = 0; i < c; i++){
        printf("digite a matrícula do aluno %d \n",i+1);
        scanf("%d", &a[i]);
        printf("Digite a nota desse aluno \n");
        scanf("%f",&b[i]);
    }
}

void printV(int * a , int b){

    printf("Alunos aprovados :\n");

    for (int t = 0; t < b ; t++){
        printf("[   %d   ]\n" , a[t]);
    }
}

int * criaAprovados(int * a , float * b , int c , int * d){
    *d = 0;
    int * aprovados;

    for (int k = 0; k < c ; k++){
        if(b[k] >= 5.0){
            *d += 1;
        }
        else {
            a[k] = 0;
        }
    }

    if (*d == 0) { //no student is aproved 
        return NULL;
    }

    aprovados = (int*)malloc(*d * sizeof(int));
    if(aprovados == NULL){
        fprintf(stderr,"“Nao foi possivel alocar espaco !\n");
        exit(-9);
    }

    int j = 0;
    for (int s = 0 ; s < c ; s++){
         if(b[s] >= 5.0 && a[s] != 0){
            aprovados[j] = a[s];
            j++;
        }
    }
    return aprovados;
}
