#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Definindo constantes
#define NUM_PROCESSES 3    // Número de processos
#define NUM_FRAMES 16      // Número de frames na memória física
#define VIRTUAL_PAGES 16   // Número de páginas virtuais por processo
#define ACCESSES_PER_PROCESS 100  // Número de acessos de memória por processo

// Estrutura para uma entrada na tabela de páginas
typedef struct {
    int frame_number;  // Número do frame
    int valid;         // Bit de validade
    int referenced;    // Bit de referência
    int modified;      // Bit de modificação
    int last_used;     // Última vez que foi usado
} PageTableEntry;

// Estrutura para um processo
typedef struct {
    PageTableEntry page_table[VIRTUAL_PAGES];  // Tabela de páginas
} Process;

// Estrutura para um frame na memória física
typedef struct {
    int frame_number;  // Número do frame
    int process_id;    // ID do processo que possui esta página
    int page_number;   // Número da página
    int modified;      // Indicador se a página foi modificada
} Frame;

// Estrutura para o gerenciador de memória
typedef struct {
    Process processes[NUM_PROCESSES];          // Lista de processos
    Frame frames[NUM_FRAMES];                  // Lista de frames
    int next_frame_to_replace[NUM_PROCESSES];  // Próximo frame a ser substituído
} MemoryManager;

MemoryManager mm;  // Instância do gerenciador de memória

// Declaração de protótipos de funções
void initialize_memory_manager();
void load_accesses(const char *filename, int accesses[][2]);
void simulate_round_robin(int rounds, const char *algorithm, int k, int pipes[NUM_PROCESSES][2]);
void handle_page_fault(int process_id, int page_number, const char *algorithm, int k);
int select_victim_frame(int process_id, const char *algorithm, int k);
void print_page_tables();
void print_memory_frames();
int find_oldest_frame(int process_id);

int main(int argc, char *argv[]) {
    // Verifica se o número de argumentos é correto
    if (argc != 3 && argc != 4) {
        printf("Usage: %s <algorithm> <rounds> [k]\n", argv[0]);
        return 1;
    }

    const char *algorithm = argv[1];  // Algoritmo de substituição de páginas
    int rounds = atoi(argv[2]);       // Número de rodadas
    int k = argc == 4 ? atoi(argv[3]) : 0;  // Parâmetro adicional para certos algoritmos

    initialize_memory_manager();  // Inicializa o gerenciador de memória

    int pipes[NUM_PROCESSES][2];  // Array para pipes de comunicação entre processos
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    pid_t pids[NUM_PROCESSES];  // Array para armazenar os PIDs dos processos filhos
    const char *filenames[] = {"P1.txt", "P2.txt", "P3.txt"};  // Arquivos de acesso de memória para cada processo
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {
            close(pipes[i][0]);  // Fecha o lado de leitura do pipe no processo filho
            int accesses[ACCESSES_PER_PROCESS][2];
            load_accesses(filenames[i], accesses);
            for (int j = 0; j < ACCESSES_PER_PROCESS; j++) {
                write(pipes[i][1], accesses[j], sizeof(accesses[j]));
            }
            close(pipes[i][1]);  // Fecha o lado de escrita do pipe no processo filho
            exit(EXIT_SUCCESS);
        } else {
            close(pipes[i][1]);  // Fecha o lado de escrita do pipe no processo pai
        }
    }

    simulate_round_robin(rounds, algorithm, k, pipes);  // Simula o agendamento round-robin

    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);  // Espera todos os processos filhos terminarem
    }

    print_page_tables();  // Imprime as tabelas de páginas
    print_memory_frames();  // Imprime os frames de memória

    return 0;
}

// Função para inicializar o gerenciador de memória
void initialize_memory_manager() {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < VIRTUAL_PAGES; j++) {
            mm.processes[i].page_table[j].frame_number = -1;
            mm.processes[i].page_table[j].valid = 0;
            mm.processes[i].page_table[j].referenced = 0;
            mm.processes[i].page_table[j].modified = 0;
            mm.processes[i].page_table[j].last_used = 0;
        }
        mm.next_frame_to_replace[i] = 0;
    }
    for (int i = 0; i < NUM_FRAMES; i++) {
        mm.frames[i].frame_number = i;
        mm.frames[i].process_id = -1;
        mm.frames[i].page_number = -1;
        mm.frames[i].modified = 0;
    }
}

// Função para carregar os acessos de memória a partir de um arquivo
void load_accesses(const char *filename, int accesses[][2]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < ACCESSES_PER_PROCESS; i++) {
        fscanf(file, "%d %d", &accesses[i][0], &accesses[i][1]);
    }
    fclose(file);
}

// Função para simular o agendamento round-robin
void simulate_round_robin(int rounds, const char *algorithm, int k, int pipes[NUM_PROCESSES][2]) {
    for (int r = 0; r < rounds; r++) {
        for (int i = 0; i < NUM_PROCESSES; i++) {
            int accesses[ACCESSES_PER_PROCESS][2];
            read(pipes[i][0], accesses, sizeof(accesses));
            for (int j = 0; j < ACCESSES_PER_PROCESS; j++) {
                int page_number = accesses[j][0];
                int write = accesses[j][1];
                PageTableEntry *pte = &mm.processes[i].page_table[page_number];
                if (!pte->valid) {
                    handle_page_fault(i, page_number, algorithm, k);
                }
                pte->referenced = 1;
                if (write) {
                    pte->modified = 1;
                }
                pte->last_used = r * ACCESSES_PER_PROCESS + j;
            }
        }
    }
}

// Função para lidar com falhas de página
void handle_page_fault(int process_id, int page_number, const char *algorithm, int k) {
    int frame_number = select_victim_frame(process_id, algorithm, k);
    Frame *frame = &mm.frames[frame_number];
    if (frame->process_id != -1) {
        mm.processes[frame->process_id].page_table[frame->page_number].valid = 0;
    }
    frame->process_id = process_id;
    frame->page_number = page_number;
    frame->modified = 0;
    mm.processes[process_id].page_table[page_number].frame_number = frame_number;
    mm.processes[process_id].page_table[page_number].valid = 1;
    mm.processes[process_id].page_table[page_number].last_used = -1;
}

// Função para selecionar o frame vítima para substituição
int select_victim_frame(int process_id, const char *algorithm, int k) {
    if (strcmp(algorithm, "lru") == 0) {
        return find_oldest_frame(process_id);
    } else if (strcmp(algorithm, "second_chance") == 0) {
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
            victim_frame = find_oldest_frame(process_id);
        }
        mm.next_frame_to_replace[process_id] = (victim_frame + 1) % NUM_FRAMES;
        return victim_frame;
    }

    int victim = mm.next_frame_to_replace[process_id];
    mm.next_frame_to_replace[process_id] = (mm.next_frame_to_replace[process_id] + 1) % NUM_FRAMES;
    return victim;
}

// Função para encontrar o frame mais antigo (LRU)
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

// Função para imprimir as tabelas de páginas
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

// Função para imprimir os frames de memória
void print_memory_frames() {
    printf("Memory Frames:\n");
    for (int i = 0; i < NUM_FRAMES; i++) {
        Frame *frame = &mm.frames[i];
        printf("Frame %d -> Process %d Page %d (modified: %d)\n", i, frame->process_id, frame->page_number, frame->modified);
    }
}
