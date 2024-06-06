// cliente.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MSG_SIZE 1024
#define FIFO1 "fifoRead"
#define FIFO2 "fifoWrite"

int main(void) {
    int fifoIn;
    int fifoOut;
    char message[MSG_SIZE];

    while (1) {
        printf("Enter a string: ");
        fgets(message, MSG_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline character

        if ((fifoIn = open(FIFO1, O_WRONLY)) < 0) {
            perror("erro ao abrir fifoRead");
            exit(1);
        }

        write(fifoIn, message, strlen(message) + 1);
        close(fifoIn);

        if ((fifoOut = open(FIFO2, O_RDONLY)) < 0) {
            perror("erro ao abrir fifoWrite");
            exit(1);
        }

        read(fifoOut, message, MSG_SIZE);
        close(fifoOut);

        printf("Response: %s\n", message);
    }

    return 0;
}
