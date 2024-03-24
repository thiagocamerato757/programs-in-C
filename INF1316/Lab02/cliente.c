#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHM_KEY 8752
#define SHM_SIZE 1024

int main(void) {
    int shm_id;
    char *shm_ptr;

    // Obter o identificador da memória compartilhada
    shm_id = shmget(SHM_KEY, SHM_SIZE, 0);
    if (shm_id == -1) {
        perror("Erro ao obter o identificador da memória compartilhada");
        exit(1);
    }

    // Associar a memória compartilhada ao espaço de endereço do processo
    shm_ptr = (char*)shmat(shm_id, 0, 0);
    if (shm_ptr == (char*)-1) {
        perror("Erro ao anexar a memória compartilhada");
        exit(1);
    }

    // Exibir a mensagem do dia
    printf("Mensagem do dia: %s\n", shm_ptr);

    // Desanexar a memória compartilhada do espaço de endereço do processo
    if (shmdt(shm_ptr) == -1) {
        perror("Erro ao desanexar a memória compartilhada");
        exit(1);
    }

    return 0;
}
