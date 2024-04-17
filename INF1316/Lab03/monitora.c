#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#define EVER \
    ;        \
    ;
int count = 0;
float preco;
int continua = 1;

void handler(int signum)
{
    if (signum == SIGUSR1)
    { // começa a ligação
        preco = 0;
    }

    if (signum == SIGUSR2)
    { // encerra a ligação
        continua = 0;
        if (count <= 60)
            preco = count * 0.02;
        else
            preco = count * 0.01;
        count = 0;
    }
}

int main(void)
{

    for (EVER)
    {
        signal(SIGUSR1, handler);
        signal(SIGUSR2, handler);

        int pid;
        int comecar;
        pid = getpid();

        printf("PID: %d\n", pid);

        printf("Deseja começar uma chamada? (1 para ligar e 0 para nao ligar)\n");
        scanf("%d", &comecar);
        
        if (comecar)
        {
            continua = 1;
            while (continua)
            {
                count++;
                printf("chamada em andamento\n");
                sleep(1);
            }
        } else {
            break;
        }

        printf("Preco: %f\n", preco);
    }

    return 0;
}