#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main (void){

    int memory, *mem_add, id, pid, status, linha;
    linha = 3;// vamos trabalhar com um Vetor simples que ira ter 27 elementos(3 matrizes 3x3), o processo pai cria e preenche essas 2 primeiras matrizes
    //e os 3 processos filhos realizam a soma de cada elemento de sua respectiva linha para poder preencher a terceira matriz
 
    // aloca a memória compartilhada
    memory = shmget (IPC_PRIVATE, (9*linha*sizeof(int)), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    // associa a memória compartilhada ao processo
    //uma única reerencia para a área compartilhada
    mem_add= (int *) shmat (memory, 0, 0); // comparar o retorno com -1 
    
    printf("valores M1:\n\n");
    for(int i = 0; i < linha; i++ ){
        mem_add[i*linha+0] = rand() % 10;
        mem_add[i*linha+1] = rand() % 10;
        mem_add[i*linha+2] = rand() % 10;
        printf("| %-2d | %-2d | %-2d |\n", mem_add[i*linha+0], mem_add[i*linha+1], mem_add[i*linha+2]);
    } 
    
    printf("valores M2:\n\n");
    for(int i = 0; i < linha; i++ ){
        mem_add[i*linha+9] = rand() % 10;
        mem_add[i*linha+10] = rand() % 10;
        mem_add[i*linha+11] = rand() % 10;
        printf("| %-2d | %-2d | %-2d |\n", mem_add[i*linha+9], mem_add[i*linha+10], mem_add[i*linha+11]);
    }

    printf("\n");
    printf("valores M3:\n\n");
    for(int i =0;i<3;i++){
        if ((id = fork()) < 0){
            puts ("Erro na criação do novo processo");
            exit (-2);
        }else if (id == 0){
        
        mem_add[i*linha+18] = mem_add[i*linha+0] + mem_add[i*linha+9];
        mem_add[i*linha+19] = mem_add[i*linha+1] + mem_add[i*linha+10];
        mem_add[i*linha+20] = mem_add[i*linha+2] + mem_add[i*linha+11];
    }else{
        waitpid (-1,&status,0);
        if(!WIFEXITED(status)){
            printf("child process failed\n");
        }
        exit(3); // termina com o processo filho atual
    }

   }
   for(int i = 0; i<3; i++){
    printf("| %-2d | %-2d | %-2d |\n", mem_add[i*linha+18], mem_add[i*linha+19], mem_add[i*linha+20]);
   }
    // libera a memória compartilhada do processo
    shmdt (mem_add);
    // libera a memória compartilhada
    shmctl (memory, IPC_RMID, 0);
    return 0;
} 