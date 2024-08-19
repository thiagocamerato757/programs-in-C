#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Definição de constantes
#define NUM_PROCESSES 3
#define NUM_FRAMES 16
#define VIRTUAL_PAGES 16
#define ACCESSES_PER_PROCESS 100

// Estrutura que representa uma entrada na tabela de páginas
typedef struct {
    int frame_number;   // Número do quadro de memória
    int valid;          // Bit de validade
    int referenced;     // Bit de referência
    int modified;       // Bit de modificação
    int last_used;      // Última vez que a página foi usada
} PageTableEntry;

// Estrutura que representa um processo, que contém uma tabela de páginas
typedef struct {
    PageTableEntry page_table[VIRTUAL_PAGES];
} Process;

// Estrutura que representa um quadro de memória
typedef struct {
    int frame_number;   // Número do quadro de memória
    int process_id;     // ID do processo dono do quadro
    int page_number;    // Número da página
    int modified;       // Bit de modificação
} Frame;

// Estrutura que gerencia a memória
typedef struct {
    Process processes[NUM_PROCESSES];
    Frame frames[NUM_FRAMES];
    int next_frame_to_replace[NUM_PROCESSES];
} MemoryManager;

// Instância global do gerenciador de memória
MemoryManager mm;

// Protótipos de funções
void initialize_memory_manager();
void load_accesses(const char *filename, int accesses[][2]);
void simulate_round_robin(int rounds, const char *algorithm, int k, int pipes[NUM_PROCESSES][2]);
void handle_page_fault(int process_id, int page_number, const char *algorithm, int k);
int select_victim_frame(int process_id, const char *algorithm, int k);
void print_page_tables();
void print_memory_frames();
int find_oldest_frame(int process_id);

int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 4) {
        printf("Usage: %s <algorithm> <rounds> [k]\n", argv[0]);
        return 1;
    }

    const char *algorithm = argv[1];
    int rounds = atoi(argv[2]);
    int k = argc == 4 ? atoi(argv[3]) : 0;

    initialize_memory_manager();

    // Criação de pipes para comunicação entre processos
    int pipes[NUM_PROCESSES][2];
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    pid_t pids[NUM_PROCESSES];
    const char *filenames[] = {"P1.txt", "P2.txt", "P3.txt"};
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {
            // Código do processo filho
            close(pipes[i][0]);  // Fecha o lado de leitura do pipe no filho

            int accesses[ACCESSES_PER_PROCESS][2];
            load_accesses(filenames[i], accesses);

            // Escreve os acessos no pipe
            for (int j = 0; j < ACCESSES_PER_PROCESS; j++) {
                write(pipes[i][1], &accesses[j], sizeof(accesses[j]));
            }

            close(pipes[i][1]);  // Fecha o lado de escrita do pipe no filho
            exit(0);
        } else {
            // Código do processo pai
            close(pipes[i][1]);  // Fecha o lado de escrita do pipe no pai
        }
    }

    simulate_round_robin(rounds, algorithm, k, pipes);

    // Espera todos os processos filhos terminarem
    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }

    return 0;
}

// Inicializa o gerenciador de memória
void initialize_memory_manager() {
    memset(&mm, 0, sizeof(MemoryManager));
    for (int i = 0; i < NUM_FRAMES; i++) {
        mm.frames[i].process_id = -1;  // -1 indica que o quadro está livre
    }
    for (int i = 0; i < NUM_PROCESSES; i++) {
        mm.next_frame_to_replace[i] = 0;
    }
}

// Carrega os acessos a partir de um arquivo
void load_accesses(const char *filename, int accesses[][2]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    for (int i = 0; i < ACCESSES_PER_PROCESS; i++) {
        fscanf(file, "%d %c", &accesses[i][0], (char *)&accesses[i][1]);
    }

    fclose(file);
}

// Simula a execução dos processos usando round-robin
void simulate_round_robin(int rounds, const char *algorithm, int k, int pipes[NUM_PROCESSES][2]) {
    int access_indices[NUM_PROCESSES] = {0};
    int accesses[NUM_PROCESSES][ACCESSES_PER_PROCESS][2];

    // Executa os rounds
    for (int i = 0; i < rounds; i++) {
        for (int p = 0; p < NUM_PROCESSES; p++) {
            int access[2];
            if (read(pipes[p][0], &access, sizeof(access)) > 0) {
                int page_number = access[0];
                char access_type = access[1];

                // Verifica se a página está na memória
                if (mm.processes[p].page_table[page_number].valid == 0) {
                    handle_page_fault(p, page_number, algorithm, k);
                }

                // Atualiza os bits de referência e modificação
                mm.processes[p].page_table[page_number].referenced = 1;
                mm.processes[p].page_table[page_number].last_used = i;  // Rastreia a última vez que foi usada
                if (access_type == 'W') {
                    mm.processes[p].page_table[page_number].modified = 1;
                }

                access_indices[p] = (access_indices[p] + 1) % ACCESSES_PER_PROCESS;
            }
        }
    }

    print_page_tables();
    print_memory_frames();
}

// Trata uma falta de página
void handle_page_fault(int process_id, int page_number, const char *algorithm, int k) {
    // Verifica se há um quadro livre
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (mm.frames[i].process_id == -1) {
            // Encontra um quadro livre e carrega a página nele
            mm.frames[i].process_id = process_id;
            mm.frames[i].page_number = page_number;
            mm.frames[i].modified = 0;

            mm.processes[process_id].page_table[page_number].frame_number = i;
            mm.processes[process_id].page_table[page_number].valid = 1;
            mm.processes[process_id].page_table[page_number].referenced = 1;
            mm.processes[process_id].page_table[page_number].modified = 0;
            mm.processes[process_id].page_table[page_number].last_used = -1;  // Inicializa o tempo de última utilização
            return;
        }
    }

    // Se não houver quadro livre, seleciona um quadro vítima para substituição
    int victim_frame = select_victim_frame(process_id, algorithm, k);
    int victim_page_number = mm.frames[victim_frame].page_number;

    // Se a página vítima foi modificada, simula a gravação em swap
    if (mm.frames[victim_frame].modified) {
        printf("Page fault: Process %d page %d replaced its own page %d (modified)\n", process_id, page_number, victim_page_number);
    } else {
        printf("Page fault: Process %d page %d replaced its own page %d\n", process_id, page_number, victim_page_number);
    }

    mm.processes[process_id].page_table[victim_page_number].valid = 0;

    // Carrega a nova página no quadro vítima
    mm.frames[victim_frame].process_id = process_id;
    mm.frames[victim_frame].page_number = page_number;
    mm.frames[victim_frame].modified = 0;

    mm.processes[process_id].page_table[page_number].frame_number = victim_frame;
    mm.processes[process_id].page_table[page_number].valid = 1;
    mm.processes[process_id].page_table[page_number].referenced = 1;
    mm.processes[process_id].page_table[page_number].modified = 0;
    mm.processes[process_id].page_table[page_number].last_used = -1;  // Inicializa o tempo de última utilização
}

// Seleciona um quadro vítima para substituição, de acordo com o algoritmo especificado
int select_victim_frame(int process_id, const char *algorithm, int k) {
    if (strcmp(algorithm, "NRU") == 0) {
        // Implementa o algoritmo NRU (Not Recently Used)
        for (int i = 0; i < NUM_FRAMES; i++) {
            if (mm.frames[i].process_id == process_id) {
                int page = mm.frames[i].page_number;
                if (!mm.processes[process_id].page_table[page].referenced && !mm.processes[process_id].page_table[page].modified) {
                    return i;
                }
            }
        }
    } else if (strcmp(algorithm, "2ndChance") == 0) {
        // Implementa o algoritmo Second Chance
        while (1) {
            int frame = mm.next_frame_to_replace[process_id];
            int page = mm.frames[frame].page_number;
            if (mm.frames[frame].process_id == process_id) {
                if (!mm.processes[process_id].page_table[page].referenced) {
                    mm.next_frame_to_replace[process_id] = (frame + 1) % NUM_FRAMES;
                    return frame;
                } else {
                    mm.processes[process_id].page_table[page].referenced = 0;
                }
            }
            mm.next_frame_to_replace[process_id] = (frame + 1) % NUM_FRAMES;
        }
    } else if (strcmp(algorithm, "LRU") == 0) {
        // Implementa o algoritmo LRU (Least Recently Used)
        int oldest_frame = find_oldest_frame(process_id);
        return oldest_frame;
    } else if (strcmp(algorithm, "WS") == 0) {
        // Implementa o algoritmo Working Set com tamanho de janela k
        int window_start = mm.next_frame_to_replace[process_id];
        int victim_frame = -1;
        for (int i = 0; i < k; i++) {
            int frame = (window_start + i) % NUM_FRAMES;
            if (mm.frames[frame].process_id == process_id) {
                victim_frame = frame;
                break;
            }
        }
        if (victim_frame == -1) {
            victim_frame = find_oldest_frame(process_id);  // Recurso de fallback para o quadro mais antigo
        }
        mm.next_frame_to_replace[process_id] = (victim_frame + 1) % NUM_FRAMES;
        return victim_frame;
    }

    // Recurso de fallback para FIFO simples
    int victim = mm.next_frame_to_replace[process_id];
    mm.next_frame_to_replace[process_id] = (mm.next_frame_to_replace[process_id] + 1) % NUM_FRAMES;
    return victim;
}

// Encontra o quadro mais antigo utilizado pelo processo
int find_oldest_frame(int process_id) {
    int oldest_frame = -1;
    int oldest_time = __INT_MAX__;
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (mm.frames[i].process_id == process_id) {
            int page = mm.frames[i].page_number;
            if (mm.processes[process_id].page_table[page].last_used < oldest_time) {
                oldest_time = mm.processes[process_id].page_table[page].last_used;
                oldest_frame = i;
            }
        }
    }
    return oldest_frame;
}

// Imprime as tabelas de páginas de todos os processos
void print_page_tables() {
    for (int p = 0; p < NUM_PROCESSES; p++) {
        printf("Process %d Page Table:\n", p);
        for (int i = 0; i < VIRTUAL_PAGES; i++) {
            PageTableEntry *pte = &mm.processes[p].page_table[i];
            printf("Page %d -> Frame %d (valid: %d, ref: %d, mod: %d)\n", i, pte->frame_number, pte->valid, pte->referenced, pte->modified);
        }
        printf("\n");
    }
}

// Imprime os quadros de memória
void print_memory_frames() {
    printf("Memory Frames:\n");
    for (int i = 0; i < NUM_FRAMES; i++) {
        Frame *frame = &mm.frames[i];
        printf("Frame %d -> Process %d Page %d (modified: %d)\n", i, frame->process_id, frame->page_number, frame->modified);
    }
}
