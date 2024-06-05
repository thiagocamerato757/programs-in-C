#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define FIFO "minhaFifo"
#define OPENMODE (O_WRONLY | O_NONBLOCK)
int main (void){
    
char mensagem[81];

int fifo;
if (access(FIFO, F_OK) == -1){
    if (mkfifo (FIFO, S_IRUSR | S_IWUSR) != 0){
        fprintf (stderr, "Erro ao criar FIFO %s\n", FIFO);
        return -1;
    }
}
puts ("Abrindo FIFO");
if ((fifo = open (FIFO, OPENMODE)) < 0){
    fprintf (stderr, "Erro ao abrir a FIFO %s\n", FIFO);
    return -2;
}
puts ("Começando a escrever...");
scanf("%s", mensagem);
printf("%s",mensagem);
write(fifo, mensagem, strlen(mensagem));
puts ("\nFim da escrita");
return 0; 
}