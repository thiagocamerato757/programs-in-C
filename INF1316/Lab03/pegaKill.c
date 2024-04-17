#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#define EVER ;;
void killHandler(int sinal);
int main (void){
    int pid;
    pid = getpid();
    printf("%d\n",pid);
    void (*p)(int); // ponteiro para função que recebe int como
     // parâmetro
    p = signal(SIGKILL, killHandler);
    printf("Endereco do manipulador anterior %p\n", p);
    for(EVER);
}
void killHandler(int sinal){
    printf("Você deu kill(%d) \n", sinal);
    exit(0);
}