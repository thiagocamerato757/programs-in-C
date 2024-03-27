#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void create_process(int *shm_addr, int *result, int *arr, int start, int end, int search){
    int i,id;
    if((id = fork()) < 0){
        puts("Erro no fork");
        exit(-2);
    }else if (id != 0) return;
    for(i = start; i < end; ++i){
        if(arr[i] == search){
            *result = i;
            break;
        }
    }
    shmdt(shm_addr);
    exit(3);
    
}
 
int main(void) {
    int memory, *mem_add, result, pid, status, tam, acha;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);

    // aloca a memória compartilhada
    memory = shmget(IPC_PRIVATE, ((tam+1) * sizeof(int)), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    // associa a memória compartilhada ao processo
    // uma única referência para a área compartilhada
    mem_add = (int *)shmat(memory, 0, 0); // comparar o retorno com -1 

    printf("Valores gerados:\n");
    for (int i = 1; i < tam+1; i++) {
        mem_add[i] = rand() % 10;
        printf("|%-2.2d|", mem_add[i]);
    }
    printf("\n");
    printf("Qual dado deseja achar ?\n");
    scanf("%d", &acha);

    for (int i = 1; i < (tam+1); i++) {
      create_process( mem_add,mem_add,mem_add+1, i, tam, acha);
      waitpid(-1,&status,0);
    }
    printf("valor no índice : %d\n",*mem_add);
    // libera a memória compartilhada do processo
    shmdt(mem_add);
    // libera a memória compartilhada
    shmctl(memory, IPC_RMID, 0);
    return 0;
}
