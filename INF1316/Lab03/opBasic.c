#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
void floatHandler(int signal);
int main(void){
    signal(SIGFPE, floatHandler);
    int n1;
    int n2;
    printf("Digite o primeiro numero: \n");
    scanf("%d", &n1);
    printf("Digite o segundo numero: \n");
    scanf("%d", &n2);
    printf("%d + %d = %d\n", n1, n2, (n1+n2));
    printf("%d - %d = %d\n", n1, n2, (n1-n2));
    printf("%d * %d = %d\n", n1, n2, (n1*n2));
    if(n2 == 0){
        float s  = n1/n2;
    }else{
        printf("%d / %d = %d\n", n1, n2, (n1/n2)) ;
    }
    return 0;
}

void floatHandler(int signal)
{
    printf("divisão por zero não pode ser feita\n");
    exit(1);
}