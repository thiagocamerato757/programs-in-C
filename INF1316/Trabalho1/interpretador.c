#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "interpretador.h"

#define PIPE_READ_END 0
#define PIPE_WRITE_END 1

// Função para enviar as informações do programa para o escalonador através da pipe
void envia_info(program *prog, int pipe_fd) {
    // Escrever os dados do programa na pipe
    if (write(pipe_fd, prog, sizeof(program)) == -1) {
        perror("Erro ao escrever na pipe");
        exit(1);
    }
}

int main(void) {
    FILE *input_file;
    program prog;
    int pipe_fd[2]; // Descritores de arquivo da pipe
    int status;
    char line[100]; // Buffer para armazenar cada linha do arquivo
    char *virgula_pos; // Ponteiro para a posição da vírgula na linha

    // Criar a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Erro ao criar a pipe");
        exit(1);
    }

    // Criar um processo filho para o escalonador
    int pid = fork();

    if (pid == -1) {
        perror("Erro ao criar o processo filho");
        exit(1);
    } else if (pid == 0) {
        // No processo filho (escalonador)
        // Fechar o descritor de escrita da pipe
        close(pipe_fd[PIPE_WRITE_END]);

        // Redirecionar o descritor de leitura da pipe para o descritor padrão de entrada
        dup2(pipe_fd[PIPE_READ_END], 0);

        // Executar o escalonador
        execl("./escalonador", "escalonador", NULL);

        perror("Erro ao executar o escalonador");
        exit(1);
    } else {
        // No processo pai
        // Fechar o descritor de leitura da pipe
        close(pipe_fd[PIPE_READ_END]);

        // Abrir o arquivo de entrada
        input_file = fopen("programas.txt", "r");
        if (input_file == NULL) {
            perror("Erro ao abrir o arquivo de entrada");
            exit(1);
        }
        printf("enviando...\n\n");
        // Ler o arquivo de entrada
        while (fgets(line, sizeof(line), input_file) != NULL) {
            // Remover o caractere de nova linha, se presente
            line[strcspn(line, "\n")] = '\0';

            // Obter o nome do programa
            virgula_pos = strchr(line, ',');
            if (virgula_pos != NULL) {
                *virgula_pos = '\0'; // Terminar a string no ponto da vírgula
                strcpy(prog.name, line);
                // Avançar o ponteiro para a próxima parte da linha
                strcpy(line, virgula_pos + 1);
            } else {
                strcpy(prog.name, line);
                line[0] = '\0'; // Limpar a linha
            }

            // Verificar se há parâmetros
            if (strstr(line, "PR=")) {
                prog.type = 'P'; // Programa de prioridade
                sscanf(line, "PR=%d", &prog.priority);
            } else if (strstr(line, "I=")) {
                prog.type = 'T'; // Programa de tempo real
                sscanf(line, "I=%d D=%d", &prog.initial_time, &prog.duration);
            } else {
                prog.type = 'R'; // Programa de round-robin
            }
            // Enviar as informações do programa para o escalonador
            envia_info(&prog, pipe_fd[PIPE_WRITE_END]);
            sleep(1);
        }

        // Fechar o descritor de escrita da pipe após enviar todos os programas
        close(pipe_fd[PIPE_WRITE_END]);
        // Fechar o arquivo de entrada
        fclose(input_file);

        // Aguardar o término do processo filho (escalonador)
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status)) {
            printf("Erro: o processo filho falhou\n");
        }
    }

    return 0;
}
