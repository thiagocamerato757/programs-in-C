//includes 
#include<stdio.h>


//structed data 

typedef struct sessao
{
    int horas;
    int minutos;

} Sessao;

typedef struct ingresso
{
    int fila;
    int assento;
    char tipo; /*I - inteira , M - meia*/
    Sessao se;
}Ingresso;

// function prototypes 
int qtdIngressos(Ingresso * ingresso);
float totalSessao (Ingresso * ingresso, int numIngressos,Sessao sessao);


//main function 
int main(void){
    //variables 
    Ingresso venda[] =
    {
        {8,1,'M',{4,30}},
        {3,5,'M',{8,0}},
        {1,7,'I',{4,30}},
        {5,5,'I',{8,0}},
        {7,1,'M',{6,0}},
        {4,3,'I',{8,0}}
    };
    Sessao sessaoSelect;
    int quantidadeTotal;
    float arrecadamento;

    //execution
    printf("Digite a sessão do formato HH,MM(horas,minutos)!\n");
    scanf("%d,%d",&sessaoSelect.horas,&sessaoSelect.minutos);
    quantidadeTotal = qtdIngressos(venda);
    arrecadamento = totalSessao(venda,quantidadeTotal,sessaoSelect);
    printf("Têm-se um total de R$ %.2f para a sessão das %d horas e %d minutos.\n"
    ,arrecadamento,sessaoSelect.horas,sessaoSelect.minutos);





    return 0;
}
//function to calculate the quantity if tickets sold
int qtdIngressos(Ingresso *ingresso) {
    int qtd = 0;
    for (int i = 0; ingresso[i].tipo != '\0'; i++) {
        qtd++;
    }
    return qtd;
}
//function that calculates the total amount of an certain session 
float totalSessao (Ingresso * ingresso, int numIngressos,Sessao sessao){
    float totalArrecadado = 0.0;
    for(int i = 0; i < numIngressos; i++){
        if((ingresso + i)->se.horas == sessao.horas && (ingresso + i)->se.minutos == sessao.minutos){
            if((ingresso+i)->tipo == 'I'){
                totalArrecadado += 30.0;
            }
            else if( (ingresso + i)->tipo == 'M'){
                totalArrecadado += 15.00;
            }
        }
    }
    if (totalArrecadado == 0.0) {
    printf("Nenhuma sessão encontrada!\n");
    return -1.0;
    }
    return totalArrecadado;
}