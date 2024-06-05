#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <wait.h>
#include "interpretador.h"

#define REAL_TIME_MAX_SECONDS_DURATION 60 // tempo de duracao maximo de um real time por vez
#define ROUND_ROBIN_TIME_INTERVAL 0.5 // fatia de tempo que um round robin executa por vez
#define PRIO_TOTAL_TIME_EXECUTION 20 // tempo maximo que um programa de prio fixa pode executar
#define ETERNAL_LOOP_TIME_EXECUTION 300 //tempo maximo que um programa de loop infinito pode executar

typedef struct ProgramNode {
    program prog;
    int globalPriority; // prioridade global - Real time tem prioridade -1, prioridades têm prioridade 0..7 e round robin tem prioridade 8
    int status;//status 1 : executando, -1: esperando para ser executado, 0:pronto para executar
    int total_seconds_executed;//guarda quanto tempo falta para o programa continuar executando 
    int pid;//ar,azena o pid do processo
    struct ProgramNode *next;
} ProgramNode;

typedef struct Sharemem {
    ProgramNode *current_program_node; //aponta pra o programa que esta executando
    ProgramNode *programsList;//armazena todos os programas lidos pelo interpretador
    time_t local;//guarda o instante que o escalonador inicia
    struct tm *secs;
}sharemem;

sharemem *shr = NULL;

ProgramNode *create_program_node(program program) {
    ProgramNode *new_node = malloc(sizeof(ProgramNode));
    if (new_node == NULL) {
        perror("Erro ao alocar memória para o nó do programa");
        exit(EXIT_FAILURE);
    }
    new_node->prog = program;
    new_node->next = NULL;
    new_node->status = 0;
    new_node->pid = -100;//inicia com um pid  qualquer
    if(program.type == 'P'){
        new_node->globalPriority = program.priority;
        new_node->total_seconds_executed = PRIO_TOTAL_TIME_EXECUTION;
    }else if(program.type == 'T'){
        new_node->globalPriority = -1;
        new_node->total_seconds_executed = ETERNAL_LOOP_TIME_EXECUTION;
    }else{
        new_node->globalPriority = -1;
        new_node->total_seconds_executed = ETERNAL_LOOP_TIME_EXECUTION;
    }
    return new_node;
}

void insert_program(ProgramNode **head, program program) {
    ProgramNode *new_node = create_program_node(program);
    if (*head == NULL) {
        *head = new_node;
    } else {
        ProgramNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}
void remove_program(ProgramNode **head, ProgramNode *program_to_remove) {
    if (*head == NULL || program_to_remove == NULL) {
        return;
    }

    if (*head == program_to_remove) {
        *head = (*head)->next;
        free(program_to_remove);
        return;
    }

    ProgramNode *current = *head;
    while (current->next != NULL && current->next != program_to_remove) {
        current = current->next;
    }

    if (current->next == program_to_remove) {
        current->next = program_to_remove->next;
        free(program_to_remove);
    }
}

void set_timer(int duration) {
    // Configurar o timer de acordo com a duração do programa
    alarm(duration);
}
void preempt_handler(int signum) {
    ProgramNode *iterator = shr->programsList;
    // Verificar se há um programa atualmente em execução
    if (shr->current_program_node == NULL) {
        shr->current_program_node = iterator;//quando nenhum programa estiver rodando, pega o primeiro da fila
    }else{
        while(iterator->next != NULL){
            if(shr->current_program_node->globalPriority>iterator->globalPriority && (iterator->status == 0 || iterator->status == -1)){
                time_t encerra = time(NULL);
                struct tm *atual = localtime(&encerra);
                shr->current_program_node->total_seconds_executed -= (atual->tm_sec - shr->secs->tm_sec);
                if(shr->current_program_node->total_seconds_executed == 0){
                    kill(shr->current_program_node->pid,SIGTERM);//termina o processo
                    remove_program(&(shr->programsList),shr->current_program_node);//retira ele da lista
                    printf("programa %s acabou\n",shr->current_program_node->prog.name);
                }else{
                    kill(shr->current_program_node->pid,SIGSTOP);//pausa o processo
                    shr->current_program_node->status = -1;//vai estar esperando para executar novamente
                    sleep(1);
                    if(iterator->prog.type == 'T'){
                        time_t current_time = time(NULL);
                        struct tm *local_time = localtime(&current_time);
                        if((shr->secs->tm_sec - local_time->tm_sec ) % iterator->prog.initial_time == 0){//esta na hora do real time executar
                            iterator->status = 1; //programa vai executar
                            shr->current_program_node = iterator;
                            return;
                        }else{
                            iterator->status = -1; // real time esta esperando para executar
                            ProgramNode *procuraRR = shr->programsList;
                            while(procuraRR->next != NULL){
                                if(procuraRR->prog.type == 'R' && (procuraRR->status == 0 || procuraRR->status == -1) ){//procura round robin pronto pra executar ou que esta esperando executar
                                    shr->current_program_node = procuraRR;
                                    return;
                                }
                                procuraRR = procuraRR->next;
                            }
                        }
                    }else{
                        if(iterator->status == -1){
                            kill(iterator->pid,SIGCONT); // continua o processo
                        }
                        iterator->status = 1; //programa vai executar
                        shr->current_program_node = iterator;
                        return;
                    }
                }
            }
            iterator = iterator->next;
        }
    }
}

void recebe_info(ProgramNode **queue, int pipe_fd) {
    printf("Recebendo informações...\n\n");
    program program;
    time(&(shr->local));
    shr->secs = localtime(&(shr->local));
    while (read(pipe_fd, &program, sizeof(program)) > 0) {
        printf("Programa: %s\n", program.name);
        printf("Tipo: %c\n", program.type);
        if (program.type == 'P') {
            printf("Prioridade: %d\n", program.priority);
        } else if (program.type == 'T') {
            printf("Instante Inicial: %d\n", program.initial_time);
            printf("Duração: %d\n", program.duration);
        }
        kill(getpid(),SIGUSR1);//manda um sinal dizendo que um programa novo foi inserido na lista
        sleep(1);
        insert_program(queue, program);
        printf("\n");
    }
}

int main(void){
    int pid;
    int status;
    int memory;
    int fd[2];

    memory = shmget(IPC_PRIVATE, (sizeof(sharemem*)), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    shr = (sharemem *)shmat(memory,0,0);
    while(1){
        pid = fork();
        if (pid == -1) {
            perror("Erro ao criar processo filho");
            exit(-1);
        }else if(pid == 0){
            signal(SIGUSR1,preempt_handler);
            close(fd[1]);
            recebe_info(&(shr->programsList),fd[0]);
            shr->current_program_node = shr->programsList;
            kill(getpid(),SIGUSR1);
            sleep(1);
            

        }else{
            waitpid(pid, &status, 0);
            if (!WIFEXITED(status)) {
                printf("Erro: o processo filho falhou\n");
            }
        }

    }
    
    return 0;
}