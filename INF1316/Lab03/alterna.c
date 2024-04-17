#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MAX_TROCAS 10
#define EVER ;;

int trocas = 0;
int pid1, pid2;

void handler(int signum) {
    if (signum == SIGUSR1) {
        printf("total de trocas : %d\n",trocas+1);
        trocas++;
        if (trocas >= MAX_TROCAS) {
            printf("terminando os processos ...\n");
            kill(pid1, SIGKILL);
            kill(pid2, SIGKILL);
        } else {
            if (trocas % 2 == 0) {
                printf("processo 1 parou, processo 2 continuou\n");
                kill(pid1, SIGSTOP);
                kill(pid2, SIGCONT);
            } else {
                printf("processo 2 parou, processo 1 continuou\n");
                kill(pid2, SIGSTOP);
                kill(pid1, SIGCONT);
            }
        }
    }
}

int main(void) {
    signal(SIGUSR1, handler);

    pid1 = fork();
    if (pid1 == 0) {
        for(EVER){
            sleep(1);
        }
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        for(EVER){
            sleep(1);
        }
        exit(0);
    }

    while (trocas < MAX_TROCAS) {
        sleep(1);
        kill(getpid(), SIGUSR1);
    }
    return 0;
}