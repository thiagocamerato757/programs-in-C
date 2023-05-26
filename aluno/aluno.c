//includes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structed data
typedef struct grauDoAluno
{
    float prova;
    float avPratica;
}Grau;

typedef struct aluno
{
    int mat;
    char nome[51];
    Grau grau;
}Aluno;

//function prototypes 
Aluno * criaAluno(int matricula , char * nome , float notaProva, float notaAvPratica);
void mostraAprovados(Aluno** alunos, int numAlunos);
//main function 
int main(void){
    //variables
    Aluno* alunos[8];

    //execution
    alunos[0] = criaAluno(1001, "João", 7.5, 8.0);
    alunos[1] = criaAluno(1002, "Maria", 6.0, 7.0);
    alunos[2] = criaAluno(1003, "Pedro", 4.5, 6.5);
    alunos[3] = criaAluno(1004, "Ana", 8.0, 7.5);
    alunos[4] = criaAluno(1005, "Carlos", 5.5, 6.0);
    alunos[5] = criaAluno(1006, "Mariana", 7.0, 8.5);
    alunos[6] = criaAluno(1007, "Lucas", 6.5, 5.0);
    alunos[7] = criaAluno(1008, "Julia", 8.5, 9.0);
    mostraAprovados(alunos, 8);

    //dealocating memory 
    for(int i = 0; i < 8 ; i++){
        free(alunos[i]);
    }

    return 0;
}
//function to dynamic allocate memory and insert data for each students 
Aluno * criaAluno(int matricula , char * nome , float notaProva, float notaAvPratica){
    Aluno * aluno;
    aluno = (Aluno *)malloc(sizeof(Aluno));
    if(aluno == NULL){
        fprintf(stderr,"Erro ao alocar memoria de aluno!\n");
        exit(1);
    }
    aluno->mat = matricula;
    strcpy(aluno->nome,nome);
    aluno->grau.prova = notaProva;
    aluno->grau.avPratica = notaAvPratica;
    return aluno;
}
//function to print the students with sum of grades greater or iqual 5.0
void mostraAprovados(Aluno** alunos, int numAlunos) {
    printf("Alunos Aprovados:\n");
    for (int i = 0; i < numAlunos; i++) {
        float grauTotal = alunos[i]->grau.prova + alunos[i]->grau.avPratica;
        if (grauTotal >= 5.0) {
            printf("Matrícula: %d, Nome: %s, Grau Total: %.2f\n", alunos[i]->mat, alunos[i]->nome, grauTotal);
        }
    }
}