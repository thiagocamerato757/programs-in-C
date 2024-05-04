#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

void recebe_info(ProgramNode **real_time_queue, ProgramNode **priority_queues, ProgramNode **round_robin_queue, int pipe_fd) {
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
            insert_program(real_time_queue, program);
        } else {
            insert_program(round_robin_queue, program);
        }
        printf("\n");
    }
}


int main(void) {
    program program;
    ProgramNode *real_time_queue = NULL; 
    ProgramNode *priority_queues[8]; 
    ProgramNode *round_robin_queue = NULL; 
    for (int i = 0; i < 8; i++) {
        priority_queues[i] = NULL;
    }

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

    free_program_list(real_time_queue);
    for (int i = 0; i < 8; i++) {
        free_program_list(priority_queues[i]);
    }
    free_program_list(round_robin_queue);

    return 0;
}
