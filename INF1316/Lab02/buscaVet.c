#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int memory, *mem_add, id, pid, status, tam, acha;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);

    // aloca a memória compartilhada
    memory = shmget(IPC_PRIVATE, (tam * sizeof(int)), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    // associa a memória compartilhada ao processo
    // uma única referência para a área compartilhada
    mem_add = (int *)shmat(memory, 0, 0); // comparar o retorno com -1 

    printf("Valores gerados:\n");
    for (int i = 0; i < tam; i++) {
        mem_add[i] = rand() % 10;
        printf("|%-2.2d|", mem_add[i]);
    }
    printf("\n");
    printf("Qual dado deseja achar ?\n");
    scanf("%d", &acha);

    for (int i = 0; i < tam; i++) {
        if ((id = fork()) < 0) {
            puts("Erro na criação do novo processo");
            exit(-2);
        } else if (id == 0) {
            if (mem_add[i] == acha) {
                printf("Valor encontrado na posicao: %d\n", i);
            }
            exit(1);
        }
    }

    // Espera por todos os processos filhos
    for (int i = 0; i < tam; i++) {
        waitpid(-1,&status,0);
        if (!WIFEXITED(status)) {
            printf("Erro no processo filho\n");
        }
    }

    // libera a memória compartilhada do processo
    shmdt(mem_add);
    // libera a memória compartilhada
    shmctl(memory, IPC_RMID, 0);
    return 0;
}
