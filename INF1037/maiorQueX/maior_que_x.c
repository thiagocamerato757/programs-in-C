/*Escreva uma função recursiva que recebe um vetor de inteiros,seu tamanho e um valor x,
e retorne o número de elementos do vetor que é maior que x.
*/

//includes
#include<stdio.h>

//function prototypes 
int maiorQueX (int n, int *v, int x);

//main function 
int main(void){
//variables
int arrayInt [] = {1,3,-20,8,93,43,-1,69,32,55}; //random array just for testing 
int numberInput;
int maioresQue;

//execution
printf("Digite o número !\n");
scanf("%d",&numberInput);
maioresQue = maiorQueX(10,arrayInt,numberInput);
printf("A quantidade de valores da array de inteiros maiores que %d são : %d\n",numberInput,maioresQue);

return 0;
}

//function that uses recursion to see if a value in an array of int is greater
//than a given number 
int maiorQueX(int n, int *v, int x) {
    if (n == 0) {
        return 0;
    } else {
        if (*v > x) {
            return 1 + maiorQueX(n - 1, v + 1, x);
        } else {
            return maiorQueX(n - 1, v + 1, x);
        }
    }
}
