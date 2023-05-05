/*Desenvolva uma função para, dada uma cadeia de caracteres, alterá‐la para que sejam 
eliminadas todas as ocorrências de uma sequência de characteres.
*/

//includes 
#include<stdio.h>
#include<string.h>   

//function prototypes
void eliminaSequenciaChar(char *str, char *sequencia);

//main function
int main(void){
    //variables 
    char palavra[100];
    char sequencia[100];

    //execution 
    printf("Digite uma palavra \n");
    scanf("%[^\n]", palavra);
    getchar();//reads the '\n' from buffer 
    printf("Digite a sequencia de chars que voce deseja eliminar\n");
    scanf("%[^\n]", sequencia);
    getchar();//reads the '\n' from buffer 
    eliminaSequenciaChar(palavra, sequencia);
    printf("Palavra modificada : %s\n", palavra);

    return 0;
}

void eliminaSequenciaChar(char *str, char *sequencia) {
    int n = strlen(str);
    int m = strlen(sequencia);
    int i, j, k;

    for (i = 0; i < n; i++) {
        if (str[i] == sequencia[0]) {
            for (j = 1, k = i+1; j < m && k < n && str[k] == sequencia[j]; j++, k++);
            if (j == m) { // sequence found
                for (k = i + m; k <= n; k++) {
                    str[k - m] = str[k];
                }
                n -= m;
                i--; // fix index because we removed m characters
            }
        }
    }
}
