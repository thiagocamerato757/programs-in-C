#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include "interpretador.h"

#define REAL_TIME_MAX_SECONDS 60
#define ROUND_ROBIN_TIME_INTERVAL 0.5

typedef struct ProgramNode {
    program prog;
    int globalPriority; // prioridade global - Real time tem prioridade 1, prioridades têm prioridade 2 e round robin tem prioridade 3 
    struct ProgramNode *next;
} ProgramNode;

// Variáveis globais para uso nos handlers de sinal
ProgramNode *current_program_node = NULL;
ProgramNode *real_time_queue = NULL;
ProgramNode *priority_queues[7] = {NULL};
ProgramNode *round_robin_queue = NULL;

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

void insert_program(ProgramNode **head, program program, int globalPriority) {
    ProgramNode *new_node = create_program_node(program);
    new_node->globalPriority = globalPriority;
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

void set_timer(int duration) {
    // Configurar o timer de acordo com a duração do programa
    alarm(duration);
}

// Definição dos handlers dos sinais
void signal_handler(int signum) {
    // Verificar se há um programa atualmente em execução
    if (current_program_node != NULL) {
        // Obter o próximo programa a ser executado
        ProgramNode *next_program = NULL;
        if (real_time_queue != NULL) {
            next_program = real_time_queue;
        } else {
            for (int i = 0; i < 7; i++) {
                if (priority_queues[i] != NULL) {
                    next_program = priority_queues[i];
                    break;
                }
            }
            if (next_program == NULL && round_robin_queue != NULL) {
                next_program = round_robin_queue;
            }
        }

        // Comparar as prioridades globais do programa atual e do próximo programa
        if (next_program != NULL && next_program->globalPriority < current_program_node->globalPriority) {
            // Se o próximo programa tiver prioridade global mais alta, enviar um sinal SIGUSR1 para preempção
            kill(getpid(), SIGUSR1);
        }
    }
}

void exec_program(ProgramNode **program_node) {
    program prog = (*program_node)->prog;
    printf("Executando programa: %s\n", prog.name);
    int pid = fork();
    if (pid == -1) {
        perror("Erro ao criar processo filho");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (prog.type == 'P') {
            // Implementação para programas de prioridade
            for (int i = 0; i < 6; i++) {
                printf("Processo PRIO %d executando\n", getpid());
                sleep(0.5);
            }
            exit(EXIT_SUCCESS);
        } else if (prog.type == 'T') {
            // Implementação para programas de tempo real
            while (1) {
                time_t current_time = time(NULL);
                struct tm *local_time = localtime(&current_time);
                if (local_time->tm_sec == prog.initial_time) {
                    printf("Tempo Real: Executando programa %s\n", prog.name);
                    sleep(prog.duration);
                }
            }
        } else if (prog.type == 'R') {
            // Implementação para programas round-robin
            while (1) {
                printf("Round-Robin: Executando programa %s\n", prog.name);
                sleep(0.5);
            }
        }
    }
}

void recebe_info(ProgramNode **real_time_queue, ProgramNode *priority_queues[], ProgramNode **round_robin_queue, int pipe_fd) {
    printf("Recebendo informações...\n\n");
    program program;
    while (read(pipe_fd, &program, sizeof(program)) > 0) {
        printf("Programa: %s\n", program.name);
        printf("Tipo: %c\n", program.type);
        if (program.type == 'P') {
            printf("Prioridade: %d\n", program.priority);
            insert_program(&priority_queues[(program.priority - 1)], program, 2); // Prioridade 2 para programas de prioridade
        } else if (program.type == 'T') {
            printf("Instante Inicial: %d\n", program.initial_time);
            printf("Duração: %d\n", program.duration);
            insert_program(real_time_queue, program, 1); // Prioridade 1 para programas de tempo real
        } else {
            insert_program(round_robin_queue, program, 3); // Prioridade 3 para programas round-robin
        }
        printf("\n");
    }
}

int main(void) {
    // Configurar o handler para o sinal SIGUSR1
    signal(SIGUSR1, signal_handler);

    program program;
    int pipe_fd = 0; // Use o descritor de arquivo correto aqui

    // Receber informações e montar as filas de programas
    recebe_info(&real_time_queue, priority_queues, &round_robin_queue, pipe_fd);

    // Loop principal para execução dos programas
    while (1) {
        // Obter o próximo programa a ser executado
        ProgramNode *next_program = NULL;
        if (real_time_queue != NULL) {
            next_program = real_time_queue;
        } else {
            for (int i = 0; i < 7; i++) {
                if (priority_queues[i] != NULL) {
                    next_program = priority_queues[i];
                    break;
                }
            }
            if (next_program == NULL && round_robin_queue != NULL) {
                next_program = round_robin_queue;
            }
        }

        // Executar o próximo programa se ele existir
        if (next_program != NULL) {
            exec_program(&next_program);
            current_program_node = next_program;
        } else {
            // Se não houver mais programas para executar, aguardar um sinal
            sleep(1);
        }
    }

    return 0;
}
