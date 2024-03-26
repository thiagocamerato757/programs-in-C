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
    printf("Processo filho %d iniciado\n", identificador);

    // Conecta-se à memória compartilhada
    mem_id = atoi(argv[2]);
    //printf("id :%d", mem_id);
    if(identificador == 1){
        mem_ptr1 = (int *)shmat(mem_id,NULL,0);
    }else{
        mem_ptr2 = (int *)shmat(mem_id, NULL, 0);

    }
    // Associa a memória compartilhada ao processo
   
    // Gera um número aleatório
    
    sleep(rand() % 5); // Introduz um pequeno atraso aleatório
    
    


    // Escreve o valor gerado na memória compartilhada
   if(identificador==1){
    mem_ptr1[1]++;
    mem_ptr1[0] = rand() % (rand()%10);
    printf("Processo filho %d gerou o valor: %d\n", identificador, mem_ptr1[0]);
    shmdt(mem_ptr1);
   }

   if(identificador==2){
    mem_ptr2[2] = rand() % (rand()%154);
    mem_ptr2[3]++;
    printf("Processo filho %d gerou o valor: %d\n", identificador, mem_ptr2[2]);
    shmdt(mem_ptr2);
   }

    // Tivemos que utilizar indices diferentes no rand() porque quando utilizamos o mesmo indice a função sorteia o mesmo número.

    // Incrementa a sequência
    
    // libera a memória compartilhada do processo
    

    return 0;
}
