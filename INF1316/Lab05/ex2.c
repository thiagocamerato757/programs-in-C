#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>

#define FIFO "meu_fifo"
#define MSG_SIZE 81
#define OPENMODE1 (O_WRONLY | O_NONBLOCK)
#define OPENMODE2 (O_RDONLY | O_NONBLOCK)

int main(void){
  int fifo;
  if (access(FIFO, F_OK) == -1){
      if (mkfifo (FIFO, S_IRUSR | S_IWUSR) != 0){
          fprintf (stderr, "Erro ao criar FIFO %s\n", FIFO);
          return -1;
      }
  }
  int pid1 = fork();
  if(pid1 == 0){
    fifo = open(FIFO, OPENMODE1);
    char msg1 [] = "Ola"; 
    write(fifo, msg1, strlen(msg1));
    close(fifo);
    exit(EXIT_SUCCESS);
  }

  int pid2 = fork();
  if (pid2 == 0){
    fifo = open(FIFO, OPENMODE1);
    char msg2 [] = "Mundo"; 
    write(fifo, msg2, strlen(msg2));
    close(fifo);
    exit(EXIT_SUCCESS);
    
  }
  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);

  fifo = open(FIFO, OPENMODE2);
  char buffer[MSG_SIZE];
  long int n = 0;
  n = read(fifo, buffer, MSG_SIZE);
  buffer[n] = '\0';
  printf("%s\n", buffer);

  close(fifo);
  return 0;
}