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

    if(argc != 3){
        printf("Numero de argumentos invalido\n");
        return 1;
    }

    // Obtém o identificador do processo filho
    int identificador = atoi(argv[1]);
    printf("Processo filho %d iniciado\n", identificador);

    // Conecta-se à memória compartilhada
    mem_id = atoi(argv[2]);

    // Associa a memória compartilhada ao processo
    mem_ptr = (int *)shmat(mem_id, NULL, 0);

    // Gera um número aleatório
    srand(time(NULL)); // Seed baseada no tempo atual + ID do processo
    sleep(rand() % 5); // Introduz um pequeno atraso aleatório
    
    escolha = rand() % MAX_SEQUENCE_NUMBER;
    printf("Processo filho %d gerou o valor: %d\n", identificador, escolha);



    // Escreve o valor gerado na memória compartilhada
   if(identificador==1)
    mem_ptr[0] = escolha;

   if(identificador==2)
    mem_ptr[2] = escolha; 

    if(identificador==1)
    mem_ptr[1]++;

    if(identificador==2)
        mem_ptr[3]++;
 

    // Incrementa a sequência
    
    // libera a memória compartilhada do processo
    shmdt(mem_ptr);

    return 0;
}
