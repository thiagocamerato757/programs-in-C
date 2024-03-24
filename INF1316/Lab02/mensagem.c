#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SHM_KEY 8752
#define SHM_SIZE 1024

int main(void) {
    int shm_id;
    char *shm_ptr;
    int pid;
    int status;

    // Criar ou obter o identificador da memória compartilhada
    shm_id = shmget(SHM_KEY, SHM_SIZE,  IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    // Associar a memória compartilhada ao espaço de endereço do processo
    shm_ptr = (char*)shmat(shm_id, 0, 0);

    // Ler a mensagem do stdin
    printf("Digite a mensagem do dia:\n");
    fgets(shm_ptr, SHM_SIZE, stdin);

    // Separar a entrada com uma marca de fim de string
    shm_ptr[strlen(shm_ptr) - 1] = '\0';

    printf("Mensagem do dia salva na memória compartilhada.\n");

    // Criar um processo filho
    pid = fork();
    if (pid < 0) {
        puts("Erro na criação do novo processo");
        exit(-2);
    } else if (pid == 0) { // Processo filho (cliente)
        // Executar o cliente
        char *args[] = {"cliente", NULL};
        execv(args[0], args);
        // Se execv retornar, ocorreu um erro
        perror("Erro ao executar cliente");
        exit(-1);
    } else { // Processo pai
        // Esperar pelo processo filho
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status)) {
            printf("O processo filho falhou\n");
        }
        // Desanexar a memória compartilhada do espaço de endereço do processo
        shmdt(shm_ptr);
        // Remover a memória compartilhada
        shmctl(shm_id, IPC_RMID, 0);
    }

    return 0;
}
