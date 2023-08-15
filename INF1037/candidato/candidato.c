//includes 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structed data 
struct candidato
{
    int inscricao;
    char nome[51];
    int idade;
    float nota;
};
typedef struct candidato Candidato;

//function prototypes
Candidato * criaCanditado(int inscri , char * name, int age , float grade);
void exibeTodosCandidatos(Candidato**cd , int numb);
Candidato * buscaInscricao( Candidato ** cd , int numb, int inscri);


//main function 
int main(void){
    //variables
    Candidato * vpCandidato[8];
    int i;
    Candidato * pont;
    int inputInscricao;

    //execution
    vpCandidato[0] = criaCanditado(444,"Luiz",34,7.8f);
    vpCandidato[1] = criaCanditado(111,"Rita",56,8.8f);
    vpCandidato[2] = criaCanditado(999,"Rute",32,7.1f);
    vpCandidato[3] = criaCanditado(555,"Dina",27,6.4f);
    vpCandidato[4] = criaCanditado(777,"Lana",35,5.3f);
    vpCandidato[5] = criaCanditado(666,"Tais",29,9.8f);
    vpCandidato[6] = criaCanditado(222,"Cris",31,7.2f);
    vpCandidato[7] = criaCanditado(333,"Vera",44,5.4f);

    exibeTodosCandidatos(vpCandidato,8);

    printf("Digite a inscrição do candidato que você deseja buscar\n");
    scanf("%d",&inputInscricao);
    pont = buscaInscricao(vpCandidato,8,inputInscricao);
    if(pont == NULL){
        printf("Candidato com inscrição %d não encontrado!\n",inputInscricao);
    }
    else{
        printf("%s %s %s %s\n", "*Inscrição*", "Nome *", "Idade*", "Nota *");
        printf("*         *      *      *      *\n");
        printf("*%6d   * %s *%4d  * %4.2f *\n\n", pont->inscricao, pont->nome, pont->idade
        , pont->nota);
        

    
    }

    //dealocating memory
    for(i = 0; i < 8; i++){
        free(vpCandidato[i]);
    }
    return 0;
}



Candidato * criaCanditado(int inscri , char * name, int age , float grade){
    Candidato * candidate;
    candidate = (Candidato*)malloc(sizeof(Candidato));
    if(candidate == NULL){
        fprintf(stderr,"Erro ao alocar memória do candidato !\n");
        return candidate;
    }
    candidate->inscricao = inscri;
    strcpy(candidate->nome,name);
    candidate->idade = age;
    candidate->nota = grade;
    return candidate;
}

void exibeTodosCandidatos(Candidato** cd, int numb) {
    printf("Candidatos:\n\n");
    printf("%-12s %-20s %-10s %s\n", "Inscrição", "Nome", "Idade", "Nota");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < numb; i++) {
        printf("%-10d %-20s %-10d %.2f\n", cd[i]->inscricao, cd[i]->nome, cd[i]->idade, cd[i]->nota);
    }
}


Candidato * buscaInscricao( Candidato ** cd , int numb, int inscri){
    for(int i = 0; i < numb ; i++){
        if(cd[i]->inscricao == inscri){
            return cd[i];
        }
    }
    return NULL;
}