#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SEQUENCE_NUMBER 10

int main(void) {
    int shm_1, shm_2, *mem_ptr1, *mem_ptr2, pid, status;
    int seq1 = -1, seq2 = -1;
    
    // aloca a memória compartilhada
    shm_1 = shmget(IPC_PRIVATE, (sizeof(int) * 2), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    shm_2 = shmget(IPC_PRIVATE, (sizeof(int) * 2), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    
    // associa a memória compartilhada ao processo
    // uma única referência para a área compartilhada
    mem_ptr1 = (int *)shmat(shm_1, 0, 0); // 1 memoria compartilhada
    mem_ptr2 = (int *)shmat(shm_2, 0, 0); // 2 memoria compartilhada
    
    // Inicializa os valores da sequência em cada área compartilhada
    mem_ptr1[1] = 0;
    mem_ptr2[1] = 0;

    if ((pid = fork()) < 0) {
        puts("Erro na criação do novo processo");
        exit(-2);
    } else if (pid == 0) {
        // Processo filho P1
        char *args[] = {"./filho", "1", NULL, NULL};
        char shm_1_arg[20];
        sprintf(shm_1_arg, "%d", shm_1); // Converte shm_1 para string
        args[2] = malloc(strlen(shm_1_arg) + 1); // Aloca memória para o argumento
        strcpy(args[2], shm_1_arg); // Copia o valor de shm_1_arg para o argumento
        execve(args[0], args, NULL);
        puts("Falha ao executar o processo filho P1");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        puts("Erro na criação do novo processo");
        exit(-2);
    } else if (pid == 0) {
        // Processo filho P2
        char *args[] = {"./filho", "2", NULL, NULL};
        char shm_2_arg[20];
        sprintf(shm_2_arg, "%d", shm_2); // Converte shm_2 para string
        args[2] = malloc(strlen(shm_2_arg) + 1); // Aloca memória para o argumento
        strcpy(args[2], shm_2_arg); // Copia o valor de shm_2_arg para o argumento
        execve(args[0], args, NULL);
        puts("Falha ao executar o processo filho P2");
        exit(1);
    }

    // Processo pai
    while (1) {
        // Espera pelos processos filhos terminarem
        waitpid(-1, &status, 0);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) {
                printf("Um processo filho terminou.\n");
                if (seq1 != mem_ptr1[1] && seq2 != mem_ptr2[1]) {
                    // Calcula o produto dos valores gerados por P1 e P2
                    int produto = mem_ptr1[0] * mem_ptr2[0];
                    printf("Produto dos valores gerados por P1 e P2: %d\n", produto);
                    break;
                } else {
                    seq1 = mem_ptr1[1];
                    seq2 = mem_ptr2[1];
                }
            } else {
                printf("Um dos processos filho falhou.\n");
                exit(1);
            }
        }
        printf("Aguardando novos valores...\n");
        sleep(1); // Espera 1 segundo antes de verificar novamente
    }

    // libera a memória compartilhada do processo
    shmdt(mem_ptr1);
    shmdt(mem_ptr2);

    // libera a memória compartilhada
    shmctl(shm_1, IPC_RMID, 0);
    shmctl(shm_2, IPC_RMID, 0);
    
    return 0;
}
