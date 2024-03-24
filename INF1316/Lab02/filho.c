#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define MAX_SEQUENCE_NUMBER 100

int main(int argc, char *argv[]) {
    int mem_id, *mem_ptr, escolha;
    int seq = 0;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <identificador>\n", argv[0]);
        exit(1);
    }

    // Obtém o identificador do processo filho
    int identificador = atoi(argv[1]);

    // Conecta-se à memória compartilhada
    mem_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
    if (mem_id == -1) {
        perror("Erro ao criar a memória compartilhada");
        exit(1);
    }

    // Associa a memória compartilhada ao processo
    mem_ptr = (int *)shmat(mem_id, NULL, 0);

    // Gera um número aleatório
    srand(time(NULL) + getpid()); // Seed baseada no tempo atual + ID do processo
    sleep(rand() % 5); // Introduz um pequeno atraso aleatório
    escolha = rand() % MAX_SEQUENCE_NUMBER;

    // Escreve o valor gerado na memória compartilhada
    *mem_ptr = escolha;

    // Incrementa a sequência
    (*mem_ptr)++;

    printf("Processo filho %d gerou o valor: %d\n", identificador, escolha);

    // libera a memória compartilhada do processo
    shmdt(mem_ptr);

    return 0;
}
