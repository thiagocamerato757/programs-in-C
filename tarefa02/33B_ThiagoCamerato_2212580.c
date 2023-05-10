//includes
#include <stdio.h>
#include <stdlib.h>

//function prototypes
FILE *abrearq(char *str, char *mode);
int mystrlen(char *a);
void mystrcpy(char *d, char *o);
void criptografaEdecifra(char *a, int b);

//simbolic variables
#define MAX_SENTENCA 80
#define MAX_TEXTO 10000

//main function 
int main(void){
    // variables
    FILE *arquivoIN;
    FILE *arquivoOUT;
    int chave;
    char sentenca[MAX_SENTENCA + 1] = "";
    char texto[MAX_TEXTO + 1] = "";
    int tamanhoSentenca;

    // execution
    arquivoIN = abrearq("texto.txt", "r");
    arquivoOUT = abrearq("arquivoBinario.bin", "wb");

    if (arquivoIN == NULL || arquivoOUT == NULL){
        fprintf(stderr, "saindo do programa !\n");
        exit(-2);
    }

    printf("Digite o valor da chave!\n");
    scanf("%d", &chave);
    // 1) encrypt a sentense and writes it to a Binary file 
    printf("TEXTO CRIPTOGRAFADO:\n\n");
    while (!feof(arquivoIN)){
        if (fgets(sentenca, MAX_SENTENCA, arquivoIN) != NULL){

            tamanhoSentenca = mystrlen(sentenca) - 1;
            *(sentenca + (mystrlen(sentenca) + 1)) = '\0';
            //printf("sentenca normal : %s\n", sentenca);
            fwrite(&tamanhoSentenca, sizeof(int), 1, arquivoOUT);
            //printf("tamanho sentenca : %d\n", tamanhoSentenca);
            criptografaEdecifra(sentenca, chave);
            fwrite(sentenca, sizeof(char), tamanhoSentenca + 2, arquivoOUT);
            //printf("sentenca criptografada : %s\n", sentenca);
            printf("%s", sentenca);
        }
    }

    fclose(arquivoIN);
    fclose(arquivoOUT);

    arquivoIN = abrearq("arquivoBinario.bin", "rb");
    //2) reads encrypted message from Binary file and decrypt it then show it to the terminal 
    printf("\nTEXTO DECIFRADO:\n\n");
    while (fread(&tamanhoSentenca, sizeof(int), 1, arquivoIN) == 1){
        //printf("tamanho Sentenca : %d\n", tamanhoSentenca);
        fread(sentenca, sizeof(char), tamanhoSentenca + 2, arquivoIN);
        //printf("Sentenca: %s\n", sentenca);
        criptografaEdecifra(sentenca, (chave) * -1);
        mystrcpy(texto + mystrlen(texto), sentenca);
        //printf("texto: %s\n",texto);
        mystrcpy(texto + (mystrlen(texto) - 1), ". ");
        //printf("texto decifrado : %s\n",texto);
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
        else if (*a >= 'a' && *a <='z'){ // upper case
            *a = (((*a - 'a') + b) % 26) + 'a'; 
        } // recursive call to next char
        criptografaEdecifra(a + 1, b);
    }
    else if (b < 0 && *a){ // decrypt a encrypted string

        if (*a >= 'A' && *a <= 'Z'){ // upper case

            *a = (((*a - 'A') + b + 26) % 26) + 'A';
        }

        else if (*a >= 'a' && *a <= 'z'){ // upper case
            *a = (((*a - 'a') + b + 26) % 26) + 'a';
        }
        // recursive call to next char
        
        criptografaEdecifra(a + 1, b);
    }
}
