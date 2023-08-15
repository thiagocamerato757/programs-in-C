/*Desenvolver uma função que leia o nome completo de alguém, por exemplo:
– João José da Silva
– Maria B. Albuquerque
e retorne uma outra cadeia com o nome na forma:
– Silva, J. J.
– Albuquerque, M. B.
*/

//includes
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

// function prototypes
int contaIniciais(char *s);
char *sobreNome(char *s);
char *sobreNome(char *s);
char *pegaIniciais(char *s);
char *formatName(char *s);


// main function
int main(void){
    // variables
    char nome[100] = "";
    char * novoNome;

    // execution
    printf("Digite seu nome: \n");
    scanf("%[^\n]", nome);
    novoNome = formatName(nome);
    printf("Nome formatado : %s\n",novoNome);
    free(novoNome);
    return 0;
}

//function that usues recursion to count the inicials of a string
int contaIniciais(char *s){
    if (*s == '\0'){
        return 0;
    }
    else{
        if (*s >= 'A' && *s <= 'Z'){
            return 1 + contaIniciais(s + 1);
        }
        else{
            return 0 + contaIniciais(s + 1);
        }
    }
}
//functon that get's the last name of a string
char *sobreNome(char *s){
    int EspacosValidos = contaIniciais(s) - 1;
    int counter = 0;
    int length = strlen(s);
    int lastSpaceIndex;

    for (int i = 0; i < length; i++){
        if (*(s + i) == ' '){
            counter++;
            if (counter == EspacosValidos){
                lastSpaceIndex = i;
                break;
            }
        }
    }

    int j = 0;
    do{
        if (j != 0 && *(s + lastSpaceIndex + j) == ' '){
            break;
        }
        else{
            j++; // calculating the length of last name
        }
    } while (*(s + lastSpaceIndex + j) != '\0');

    int tamanhoSobrenome = j-1;
    char *lastName = (char *)malloc((tamanhoSobrenome + 3) * sizeof(char)); // 2 for ", " and 1 for null char
    if (lastName == NULL){
        fprintf(stderr, "Erro ao alocar memória do sobrenome !\n");
        exit(1);
    }

    for (int j = 0; j < tamanhoSobrenome; j++){
        *(lastName + j) = *(s + lastSpaceIndex + j + 1);
    }
    
    *(lastName + tamanhoSobrenome) = ',';
    *(lastName + tamanhoSobrenome + 1) = ' ';
    *(lastName + tamanhoSobrenome + 2) = '\0';

    return lastName;
}
//function to get all the inicials of a string
char *pegaIniciais(char *s){
    char *iniciais;
    int qtdIniciais = contaIniciais(s) - 1;
    
    iniciais = (char *)malloc((2 * qtdIniciais + 1) * sizeof(char));
    if (iniciais == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória das iniciais!\n");
        exit(1);
    }
    int i = 0;
    int j = 0;
    int espacosAteSobrenome = 0;
    while (espacosAteSobrenome  < qtdIniciais)
    {
        if(*(s+i) == ' ')
        {
            espacosAteSobrenome++;
        }
        if (*(s + i) >= 'A' && *(s + i) <= 'Z')
        {
            *(iniciais + j) = *(s + i);
            *(iniciais + j + 1) = '.';
            j += 2;
        }
        i++;
    }

    *(iniciais + j) = '\0';
    return iniciais;
}

//function to format a string (lastname, inicials.)
char *formatName(char *s){
    char *nome = sobreNome(s);
    char *iniciais = pegaIniciais(s);
    char *criaNome;

    int tamanhoAlocado = strlen(nome) + strlen(iniciais) + 1;

    criaNome = (char *)malloc(tamanhoAlocado * sizeof(char));
    if (criaNome == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória do nome formatado!\n");
        exit(1);
    }

    strcpy(criaNome, nome);
    strcat(criaNome, iniciais);

    free(nome);
    free(iniciais);

    return criaNome;
}

