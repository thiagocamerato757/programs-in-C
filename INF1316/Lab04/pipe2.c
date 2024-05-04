#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>
int main(void)
{
int fd; /* descritor a ser duplicado */
int fd2;
char buff[200];
int retorno; /* valor de retorno de dup */
int retorno2; /* valor de retorno de dup2 */
if ((fd=open("Entrada.txt",O_RDWR|O_CREAT,0666)) == -1)
{
    perror("Error open()");
    return -1;
}
if ((fd2=open("Saida.txt",O_RDWR|O_CREAT,0666)) == -1)
{
    perror("Error open()");
    return -1;
}
close(0); /* fechamento da entrada stdin */
if ((retorno = dup(fd)) == -1){ /* duplicacao de stdin (menor descritor fechado) */
    perror("Error dup-1()");
    return -2;
}
scanf(" %[^\n]",buff);
close(1);
if ((retorno2 = dup(fd2)) == -1)
{ /* duplicacao de stdout */
    perror("Error dup-2()");
    return -3;
}
printf("%s",buff);

return 0;
} 