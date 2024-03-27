#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define MAX_SEQUENCE_NUMBER 100

int main(int argc, char *argv[]) {
    int mem_id, *mem_ptr1, *mem_ptr2, escolha;
    int seq = 0;

    if(argc != 3){
        printf("Numero de argumentos invalido\n");
        return 1;
    }

    // Obtém o identificador do processo filho
    int identificador = atoi(argv[1]);

    // Conecta-se à memória compartilhada
    mem_id = atoi(argv[2]);

    if(identificador == 1){
        mem_ptr1 = (int *)shmat(mem_id,NULL,0);
    }else{
        mem_ptr2 = (int *)shmat(mem_id, NULL, 0);

    }

    // Escreve o valor gerado na memória compartilhada
   if(identificador == 1){
        sleep(rand() % 10); // Introduz um pequeno atraso aleatório
        printf("Processo filho %d iniciado\n", identificador);   
        mem_ptr1[0] = rand() % MAX_SEQUENCE_NUMBER;
        printf("Processo filho %d gerou o valor: %d\n", identificador, mem_ptr1[0]);
        mem_ptr1[1]++;// Incrementa a sequência
        //printf("%d\n",mem_ptr1[1]);
        shmdt(mem_ptr1);    // libera a memória compartilhada do processo
   }

   if(identificador == 2){
        sleep(rand() % 15); // Introduz um pequeno atraso aleatório
        printf("Processo filho %d iniciado\n", identificador);   
        mem_ptr2[2] = rand() % (MAX_SEQUENCE_NUMBER+1);
        printf("Processo filho %d gerou o valor: %d\n", identificador, mem_ptr2[2]);
        mem_ptr2[3]++; // Incrementa a sequência
        //printf("%d\n",mem_ptr2[1]);
        shmdt(mem_ptr2); // libera a memória compartilhada do processo
   }

    // Tivemos que utilizar indices diferentes no rand() porque quando utilizamos o mesmo indice a função sorteia o mesmo número, pois o mesmo gera uma mesma seed para ambos os processos,
    //ou seja, são pseudo aleatórios    

    return 0;
}
