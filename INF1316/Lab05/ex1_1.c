#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#define FIFO "minhaFifo"
#define OPENMODE (O_RDONLY | O_NONBLOCK)

int main (void){
    int fifo;
    char ch;
    if (access(FIFO, F_OK) == -1){
        if (mkfifo (FIFO, S_IRUSR | S_IWUSR) != 0){
            fprintf (stderr, "Erro ao criar FIFO %s\n", FIFO);
            return -1;
        }
    }
    if ((fifo = open (FIFO, OPENMODE)) < 0){
        fprintf (stderr, "Erro ao abrir a FIFO %s\n", FIFO);
        return -2;
    }
    while (1){
        while(read (fifo, &ch, sizeof(ch)) > 0){
            putchar(ch);
            fflush(stdout);
        }
    }
        puts ("Fim da leitura");
        close (fifo);
    
    return 0;
}