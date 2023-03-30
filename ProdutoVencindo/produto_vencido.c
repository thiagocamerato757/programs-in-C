/*A vigilância sanitária do reino TãoTãoPróximo autua os supermercados visitados conforme o número
de produtos fora da validade. Em toda esta questão, considere que cada data é representada por três
números inteiros, correspondentes a dia, mês e ano, respectivamente.
• Escreva uma função produto_vencido, que recebe a data da visita e a data de validade do produto
e retorna 1 caso o produto esteja fora da validade ou 0, caso contrário.
• Escreva uma função calcula_multa, que recebe a quantidade de produtos conferidos e a
quantidade de produtos fora da validade, e retorna o valor da multa, de acordo com as seguintes
regras:
o 0, caso nenhum produto conferido esteja fora da validade;
o R$ 100,00, caso até 10% dos produtos conferidos estejam fora da validade;
o R$ 10.000,00, caso mais de 10% e até 30% dos produtos conferidos estejam fora da
validade; e
o R$ 100.000,00, caso mais de 30% dos produtos conferidos estejam fora da validade.
Faça um programa em C que inicialmente capture a data da visita ao supermercado. Em seguida, para
cada produto conferido, capture o código do produto (um número inteiro) e a data do seu
vencimento, mostrando para cada produto se ele está ou não na validade. A entrada de dados é
finalizada quando for digitado um código de produto negativo. Seu programa deverá então calcular e
exibir o valor da multa, caso haja, ou informar que o supermercado está isento de multas.
*/

//libraries 
#include <stdio.h>

//function prototypes 
int produto_vencido (int a, int b , int c , int d, int e, int f);
int calcula_multa(int n , int m );

//main function 

int main (void){

//variables
int codigoProduct; 
int diaA;
int mesA;
int anoA;
int diaB;
int mesB;
int anoB;
int qtdProdutos = 1;
int productVencido = 0;
int productConfere;
int multa;

printf("digite a data de visita [ex : dd/mm/yyyy ]!\n");
scanf("%d / %d / %d",&diaA,&mesA,&anoA);

do { 
  printf("digite o código do produto :\n");
  scanf("%d",&codigoProduct);
  if(codigoProduct < 0){
    break;
  }
  printf("digite a data de vencimento [ex : dd/mm/yyyy ]!\n");
  scanf("%d / %d / %d",&diaB,&mesB,&anoB);
  productConfere = produto_vencido(diaA,mesA,anoA,diaB,mesB,anoB);
  if (productConfere == 1){
    printf("produto %d : Vencido !\n", qtdProdutos);
    productVencido +=1;
    qtdProdutos++;
  }
  else{
    printf("produto %d : Não vencido !\n",qtdProdutos);
    qtdProdutos++;
  }
  
} 
while(codigoProduct >= 0);

multa = calcula_multa(qtdProdutos,productVencido);
if(multa == 0){
  printf("O vendedor está insento das multas !\n");
}
else {
  printf ("total a se pagar : %d\n",multa);
}
  
return 0;
}

//function to see the if the product is expired(returning 1) or not (returning 0) comapring the visitation date to the product's expiration date
int produto_vencido (int a, int b , int c , int d, int e, int f) {
    if (c > f || c == f && b > e || c==f && b==e && a > d){
      return 1;
    }
    else return 0;
}    

//function to calculate the quantity of money the seller has to pay due to expired products 
int calcula_multa(int n , int m ){
  if ( m == 0){
    return 0;
  }

  else if (m/n == 0.1){
    return 100;
  }

  else if ( m/n > 0.1 || m/n <= 0.3){
    return 10000;
  }

  else if ( m/n > 0.3 ){
    return 100000;
  }
}