#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

void childhandler(int signo);
int delay;
int main (int argc, char *argv[]){
    int pid;
    signal(SIGCHLD, childhandler);
    if ((pid = fork()) < 0){
        fprintf(stderr, "Erro ao criar filho\n");
        exit(-1);
    }
    if (pid == 0) /* child */
    execve(argv[2], argv, 0); /* ou sleep(3);*/

    else {
        sscanf(argv[1], "%d", &delay); /* read delay from command line */
        sleep(delay);
        printf("Program %s exceeded limit of %d seconds!\n", argv[2], delay);
        kill(pid, SIGKILL);
        sleep(1); /* necessary for SIGCHLD to arrive */
    }
    return 0;
}
void childhandler(int signo) /* Executed if child dies before parent */{
    int status;
    int pid = wait(&status);
    printf("Child %d terminated within %d seconds com estado %d.\n", pid, delay, status);
    exit(0);
}