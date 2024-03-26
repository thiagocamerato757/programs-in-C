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
    int shm, *mem_ptr, pid, status;
    int seq1 = -1, seq2 = -1;
    
    // aloca a memória compartilhada
    shm = shmget(IPC_PRIVATE, (sizeof(int) * 4), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    
    // associa a memória compartilhada ao processo
    // uma única referência para a área compartilhada
    mem_ptr = (int *)shmat(shm, 0, 0); // 1 memoria compartilhada

    

    if ((pid = fork()) < 0) {
        puts("Erro na criação do novo processo");
        exit(-2);
    } else if (pid == 0) {
        // Processo filho P1
        char *args[] = {"filho", "1", NULL, NULL};
        char shm_1_arg[20];
        sprintf(shm_1_arg, "%d", shm); // Converte shm_1 para string
        args[2] = malloc(strlen(shm_1_arg) + 1); // Aloca memória para o argumento
        strcpy(args[2], shm_1_arg); // Copia o valor de shm_1_arg para o argumento
        execv(args[0], args);
        puts("Falha ao executar o processo filho P1");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        puts("Erro na criação do novo processo");
        exit(-2);
    } else if (pid == 0) {
        // Processo filho P2
        char *args[] = {"filho", "2", NULL, NULL};
        char shm_2_arg[20];
        sprintf(shm_2_arg, "%d", (shm+2)); // Converte shm_2 para string
        args[2] = malloc(strlen(shm_2_arg) + 1); // Aloca memória para o argumento
        strcpy(args[2], shm_2_arg); // Copia o valor de shm_2_arg para o argumento
        execv(args[0], args);
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
                if (seq1 != mem_ptr[1] && seq2 != mem_ptr[3]) {
                    // Calcula o produto dos valores gerados por P1 e P2
                    int produto = mem_ptr[0] * mem_ptr[2];
                    printf("Produto dos valores gerados por P1 e P2: %d\n", produto);
                    break;
                } else {
                    seq1 = mem_ptr[1];
                    seq2 = mem_ptr[3];
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
    shmdt(mem_ptr);

    // libera a memória compartilhada
    shmctl(shm, IPC_RMID, 0);
    
    return 0;
}
