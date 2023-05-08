/*Desenvolver uma função que leia o nome completo de alguém, por exemplo:
– João José da Silva
– Maria B. Albuquerque
e retorne uma outra cadeia com o nome na forma:
– Silva, J. J.
– Albuquerque, M. B.
*/

// includes
#include <stdio.h>
#include <string.h>

// function prototypes
void formataNome(char *name, char *newName);

// main function
int main(void){
    // variables
    char nome[100] = "";
    char novoNome[100] = "";

    // execution
    printf("Digite seu nome: \n");
    scanf("%[^\n]", nome);
    formataNome(nome,novoNome);
    printf("Nome formatado : %s\n",novoNome);
    return 0;
}

void formataNome(char *name, char *newName) {
    // Find the last whitespace in the name
    char *sobrenome = strrchr(name, ' ');

    // Check if the name has a last name
    if (sobrenome != NULL) {
        // Copy the last name to the destination string
        strcpy(newName, sobrenome + 1);
        strcat(newName, ", ");

        // Copy the initials of the given names
        char *ptr = name;
        while (*ptr) {
            if (*ptr != ' ' && (*(ptr - 1) == ' ' || ptr == name)) {
                strncat(newName, ptr, 1);
                strcat(newName, ".");
            }
            ptr += 1; 
        }

        // Remove the extra space after the last initial
        int length = strlen(newName);
        newName[length - 2] = '\0';
    } else {
        // If there is no last name, return the full name
        strcpy(newName, name);
    }
}
