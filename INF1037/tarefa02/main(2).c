//Thiago Pereira Camerato - 2212580

//includes
#include <stdio.h>
#include <stdlib.h>

//simbolic variables
#define MAX_SENTENCA 80
#define MAX_TEXTO 10000

//function prototypes
FILE *abrearq(char *str, char *mode);
int mystrlen(char *a);
void mystrcpy(char *d, char *o);
void criptografaEdecifra(char *a, int b);


//main function 
int main(void){
    // variables
    FILE *arquivoIN;
    int chave;
    char sentenca[MAX_SENTENCA + 1] = "";
    char texto[MAX_TEXTO + 1] = "";
    int tamanhoSentenca;

    // execution
   arquivoIN = abrearq("arquivoBinario.bin", "rb");

    if (arquivoIN == NULL){
        fprintf(stderr, "saindo do programa !\n");
        exit(-2);
    }

    printf("Digite o valor(negativo) da chave para decifrar!\n");
    scanf("%d", &chave);
    
    //2) reads encrypted message from Binary file and decrypt it then show it to the terminal 
    printf("TEXTO DECIFRADO:\n\n");
    while (fread(&tamanhoSentenca, sizeof(int), 1, arquivoIN) == 1){
        fread(sentenca, sizeof(char), tamanhoSentenca + 2, arquivoIN);
        criptografaEdecifra(sentenca, chave);
        mystrcpy(texto + mystrlen(texto), sentenca);
        mystrcpy(texto + (mystrlen(texto) - 1), ". ");
    }
    printf("%s\n\n",texto);
    fclose(arquivoIN);

    return 0;
}
// function to open a file
FILE *abrearq(char *str, char *mode){
    FILE *arq = fopen(str, mode);
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo !\n");
        return NULL;
    }
    return arq;
}
// function to calculate and return the size of a string
int mystrlen(char *a){

    int contador = 0;

    while (*a){
        contador++;
        a++;
    }
    return contador;
}

// function that copies each char of a string o into a new string
void mystrcpy(char *d, char *o){

    while (*o != '\0'){
        *d = *o;
        d++;
        o++;
    }
    *d = *o; // adds null char in the final of the string "d"
}

// function that uses a key to encrypt or decrypt a string
void criptografaEdecifra(char *a, int b){
    if (b > 0 && *a){ // encrypt a string
        if (*a >= 'A' && *a <= 'Z'){ // upper case
            *a = (((*a - 'A') + b) % 26) + 'A';
        }   
        else if (*a >= 'a' && *a <='z'){ // lower case
            *a = (((*a - 'a') + b) % 26) + 'a'; 
        } // recursive call to next char
        criptografaEdecifra(a + 1, b);
    }
    else if (b < 0 && *a){ // decrypt a encrypted string

        if (*a >= 'A' && *a <= 'Z'){ // upper case

            *a = (((*a - 'A') + b + 26) % 26) + 'A';
        }

        else if (*a >= 'a' && *a <= 'z'){ // lower case
            *a = (((*a - 'a') + b + 26) % 26) + 'a';
        }
        // recursive call to next char 
        criptografaEdecifra(a + 1, b);
    }
}
