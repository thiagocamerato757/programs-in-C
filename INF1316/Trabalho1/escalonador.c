#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "interpretador.h"
#define REAL_TIME_MAX_SECONDS 60
#define ROUND_ROBIN_TIME_INTERVAL 0.5

typedef struct ProgramNode {
    program prog;
    struct ProgramNode *next;
} ProgramNode;

void set_timer(int duration) {
    // Configurar o timer de acordo com a duração do programa
    alarm(duration);
}

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
            insert_program(&priority_queues[(program.priority -1)], program);
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
    int pid = fork();
    if (pid == -1) {
        perror("Erro ao criar processo filho");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Configurar o handler para o sinal de alarme
        signal(SIGALRM, alarm_handler);
        if (prog.type == 'P') {
            // Implementação para programas de prioridade
            for (int i = 0; i < 6; i++) {
                printf("Processo PRIO %d executando\n", getpid());
                sleep(0.5);
            }
            exit(EXIT_SUCCESS);
        } else if (prog.type == 'T') {
            // Verificar se já existe um programa em execução
            if (getpid() == 0) {
                // Configurar o temporizador para o tempo de execução
                set_timer(prog.duration);
                // Simular a execução do programa em tempo real
                while (1) {
                    // Inserir aqui o código do programa em tempo real
                }
            } else {
                // Pegar o próximo programa da fila de tempo real que ainda não está em execução
                ProgramNode *next_program = get_next_real_time_program();
                if (next_program != NULL) {
                    exec_program(&next_program);
                } else {
                    // Se não houver mais programas em tempo real, verificar se há programas round-robin na fila
                    ProgramNode *round_robin_program = get_next_round_robin_program();
                    if (round_robin_program != NULL) {
                        // Executar o programa round-robin por um período determinado pela sua duração
                        printf("Executando programa Round-Robin: %s\n", round_robin_program->prog.name);
                        sleep(round_robin_program->prog.duration);
                    }
                }
            }
        } else if (prog.type == 'R') {
            // Verificar se já existe um programa em execução
            if (getpid() == 0) {
                // Configurar o temporizador para o intervalo de tempo
                set_timer(ROUND_ROBIN_TIME_INTERVAL);
                // Simular a execução do programa round-robin
                while (1) {
                    // Inserir aqui o código do programa round-robin
                }
            } else {
                // Pegar o próximo programa da fila round-robin que ainda não está em execução
                ProgramNode *next_program = get_next_round_robin_program();
                if (next_program != NULL) {
                    exec_program(&next_program);
                }
            }
        }
    }
}


program* get_next_real_time_program(ProgramNode *real_time_queue) {
    program *next_program = NULL;
    ProgramNode *current = real_time_queue;
    time_t current_time = time(NULL);
    int min_initial_time = INT_MAX;

    while (current != NULL) {
        if (current->prog.initial_time < min_initial_time && current->prog.initial_time >= current_time) {
            // Encontrou um programa com instante inicial menor
            next_program = &(current->prog);
            min_initial_time = current->prog.initial_time;
        } else if (current->prog.initial_time == min_initial_time && current->prog.duration < next_program->duration) {
            // Encontrou um programa com mesmo instante inicial, mas menor duração
            next_program = &(current->prog);
        }
        current = current->next;
    }

    return next_program;
}

program* get_next_priority_program(ProgramNode *priority_queues[]) {
    program *next_program = NULL;
    int i = 0;

    // Procurar na fila de prioridade mais alta (prioridade 1) e subsequentemente
    while (i < 7 && next_program == NULL) {
        if (priority_queues[i] != NULL) {
            next_program = &(priority_queues[i]->prog);
        }
        i++;
    }

    return next_program;
}

program* get_next_round_robin_program(ProgramNode **round_robin_queue) {
    program *next_program = NULL;

    // Verificar se há algum programa na fila de round-robin
    if (*round_robin_queue != NULL) {
        next_program = &((*round_robin_queue)->prog);
    }

    return next_program;
}

program* get_next_program(ProgramNode *real_time_queue, ProgramNode *priority_queues[], ProgramNode *round_robin_queue) {
    program *next_program = NULL;

    // Primeiro, verificar se há programas em tempo real
    next_program = get_next_real_time_program(real_time_queue);

    // Se não houver programas em tempo real, verificar os de prioridade
    if (next_program == NULL) {
        next_program = get_next_priority_program(priority_queues);
    }

    // Se não houver programas de prioridade, verificar os de round-robin
    if (next_program == NULL) {
        next_program = get_next_round_robin_program(&round_robin_queue);
    }

    return next_program;
}

void start_program_handler(int signum) {
    // Obter o próximo programa a ser executado de acordo com a política de escalonamento
    program *next_program = get_next_program(real_time_queue, priority_queues, round_robin_queue);

    // Verificar se há algum programa disponível para execução
    if (next_program != NULL) {
        // Executar o programa
        execute_program(*next_program);
    }
}

void stop_program_handler(int signum) {
    // Implemente a lógica para interromper a execução do programa aqui
}

void alarm_handler(int signum) {
    // Tratamento do sinal de alarme
    printf("Programa interrompido devido ao sinal de alarme.\n");
    exit(EXIT_SUCCESS);
}
int main(void) {
    program program;
    ProgramNode *real_time_queue = NULL; 
    ProgramNode *priority_queues[7] = {NULL}; 
    ProgramNode *round_robin_queue = NULL; 

    int pipe_fd = 0; // Use o descritor de arquivo correto aqui

    recebe_info(&real_time_queue, priority_queues, &round_robin_queue, pipe_fd);

    printf("Programas Real Time:\n");
    print_program_list(real_time_queue);
    printf("Programas Prioridade:\n");
    for (int i = 0; i < 7; i++) {
        printf("Prioridade %d:\n", i+1);
        print_program_list(priority_queues[i]);
    }
    printf("Programas Round Robin:\n");
    print_program_list(round_robin_queue);
    // while(1){
    //     // Executar programas de cada tipo
    //     if (real_time_queue != NULL) {
    //         exec_program(&real_time_queue);
    //     }else{
    //         for (int i = 0; i < 8; i++) {
    //             if(i == 0){
    //                 if (priority_queues[0] != NULL){
    //                     exec_program(&priority_queues[0]);
    //                 }
    //             }else{
    //                 if (priority_queues[i] != NULL && priority_queues[i-1]==NULL) {
    //                     exec_program(&priority_queues[i]);
    //                 }
    //             }
    //         }
    //         if (round_robin_queue != NULL) {
    //             exec_program(&round_robin_queue);
    //         }
    //     }
    // }

    // Liberar memória das listas de programas
    free_program_list(real_time_queue);
    for (int i = 0; i < 8; i++) {
        free_program_list(priority_queues[i]);
    }
    free_program_list(round_robin_queue);

    return 0;
}
