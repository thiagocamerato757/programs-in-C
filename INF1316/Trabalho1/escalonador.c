#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "interpretador.h"

typedef struct ProgramNode {
    program prog;
    struct ProgramNode *next;
} ProgramNode;

ProgramNode *create_program_node(program program) {
    ProgramNode *new_node = malloc(sizeof(ProgramNode));
    if (new_node == NULL) {
        perror("Erro ao alocar memória para o nó do programa");
        exit(EXIT_FAILURE);
    }
    new_node->prog = program;
    new_node->next = NULL;
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

void free_program_list(ProgramNode *head) {
    ProgramNode *current = head;
    while (current != NULL) {
        ProgramNode *temp = current;
        current = current->next;
        free(temp);
    }
}

void print_program_list(ProgramNode *head) {
    ProgramNode *current = head;
    while (current != NULL) {
        printf("Nome: %s, Tipo: %c\n", current->prog.name, current->prog.type);
        current = current->next;
    }
}

int check_real_time_conflict(ProgramNode *queue, program new_program) {
    while (queue != NULL) {
        if (new_program.initial_time >= queue->prog.initial_time &&
            new_program.initial_time < queue->prog.initial_time + queue->prog.duration) {
            printf("Conflito de escalonamento em tempo real: Novo programa %s com I=%d e D=%d entra em conflito com %s\n",
                   new_program.name, new_program.initial_time, new_program.duration, queue->prog.name);
            return 1;
        } else if (new_program.initial_time + new_program.duration > queue->prog.initial_time &&
                   new_program.initial_time + new_program.duration <= queue->prog.initial_time + queue->prog.duration) {
            printf("Conflito de escalonamento em tempo real: Novo programa %s com I=%d e D=%d entra em conflito com %s\n",
                   new_program.name, new_program.initial_time, new_program.duration, queue->prog.name);
            return 1;
        }
        queue = queue->next;
    }
    return 0;
}

void recebe_info(ProgramNode **real_time_queue, ProgramNode *priority_queues[], ProgramNode **round_robin_queue, int pipe_fd) {
    printf("Recebendo informações...\n\n");
    program program;
    while (read(pipe_fd, &program, sizeof(program)) > 0) {
        printf("Programa: %s\n", program.name);
        printf("Tipo: %c\n", program.type);
        if (program.type == 'P') {
            printf("Prioridade: %d\n", program.priority);
            insert_program(&priority_queues[program.priority], program);
        } else if (program.type == 'T') {
            printf("Instante Inicial: %d\n", program.initial_time);
            printf("Duração: %d\n", program.duration);
            if (!check_real_time_conflict(*real_time_queue, program)) {
                insert_program(real_time_queue, program);
            }
        } else {
            insert_program(round_robin_queue, program);
        }
        printf("\n");
    }
}

void exec_program(ProgramNode **program_node) {
    program prog = (*program_node)->prog;
    printf("Executando programa: %s\n", prog.name);
    pid_t pid = fork();
    if (pid == -1) {
        perror("Erro ao criar processo filho");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (prog.type == 'P') {
            for (int i = 0; i < 6; i++) {
                printf("Processo PRIO %d executando\n", getpid());
                sleep(0.5);
            }
            exit(EXIT_SUCCESS);
        } else if (prog.type == 'T') {
            while (1) {
                time_t current_time = time(NULL);
                struct tm *local_time = localtime(&current_time);
                if (local_time->tm_sec == prog.initial_time) {
                    printf("Tempo Real: Executando programa %s\n", prog.name);
                    sleep(prog.duration);
                }
            }
        } else if (prog.type == 'R') {
            while (1) {
                printf("Round-Robin: Executando programa %s\n", prog.name);
                sleep(0.5);
            }
        }
    }
}

int main(void) {
    program program;
    ProgramNode *real_time_queue = NULL; 
    ProgramNode *priority_queues[8] = {NULL}; 
    ProgramNode *round_robin_queue = NULL; 

    int pipe_fd = 0; // Use o descritor de arquivo correto aqui

    recebe_info(&real_time_queue, priority_queues, &round_robin_queue, pipe_fd);

    printf("Programas Real Time:\n");
    print_program_list(real_time_queue);
    printf("Programas Prioridade:\n");
    for (int i = 0; i < 8; i++) {
        printf("Prioridade %d:\n", i);
        print_program_list(priority_queues[i]);
    }
    printf("Programas Round Robin:\n");
    print_program_list(round_robin_queue);
    while(1){
        // Executar programas de cada tipo
        if (real_time_queue != NULL) {
            exec_program(&real_time_queue);
        }else{
            for (int i = 0; i < 8; i++) {
                if(i == 0){
                    if (priority_queues[0] != NULL){
                        exec_program(&priority_queues[0]);
                    }
                }else{
                    if (priority_queues[i] != NULL && priority_queues[i-1]==NULL) {
                        exec_program(&priority_queues[i]);
                    }
                }
            }
            if (round_robin_queue != NULL) {
                exec_program(&round_robin_queue);
            }
        }
    }

    // Liberar memória das listas de programas
    free_program_list(real_time_queue);
    for (int i = 0; i < 8; i++) {
        free_program_list(priority_queues[i]);
    }
    free_program_list(round_robin_queue);

    return 0;
}
