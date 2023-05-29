//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structed data
typedef struct ingrediente {
    char nome[21];
    int qtd;
} Ingrediente;

typedef struct receita {
    char nome[26];
    int n;
    Ingrediente v[10];
} Receita;

//function prototypes
void preencherReceita(Receita* r);
int compararStrings(const char* str1, const char* str2);
void buscarReceitaPorNome(Receita** receitas, int numReceitas, char* nome);
void buscarReceitasPorIngrediente(Receita** receitas, int numReceitas, char* ingrediente);

//main function 
int main(void) {
    //variables
    Receita* receitas[5];
    char nomeBusca[26];
    char ingredienteBusca[21];

    //execution
    for (int i = 0; i < 5; i++) {
        receitas[i] = (Receita*)malloc(sizeof(Receita));
        if(receitas[i] == NULL){
            fprintf(stderr,"Erro ao alocar memória da receita de número %d",i+1);
            exit(1);
        }
        preencherReceita(receitas[i]);
        printf("-------------------------\n");
    }

    printf("Enter the name of the recipe you want to search: ");
    scanf(" %s", nomeBusca);
    buscarReceitaPorNome(receitas, 5, nomeBusca);
    printf("-------------------------\n");

    printf("Enter the name of the ingredient you want to search: ");
    scanf(" %s", ingredienteBusca);
    buscarReceitasPorIngrediente(receitas, 5, ingredienteBusca);
    printf("-------------------------\n");

    // Free allocated memory
    for (int i = 0; i < 5; i++) {
        free(receitas[i]);
    }

    return 0;
}

// Function to fill in the details of a recipe
void preencherReceita(Receita* r) {
    printf("Enter the name of the recipe: ");
    scanf("%s", r->nome);
    printf("Enter the number of ingredients: ");
    scanf("%d", &(r->n));

    printf("Fill in the ingredients:\n");
    for (int i = 0; i < r->n; i++) {
        printf("Ingredient %d:\n", i + 1);
        printf("Name: ");
        scanf(" %s", r->v[i].nome);
        printf("Quantity: ");
        scanf("%d", &(r->v[i].qtd));
    }
}

// Function to compare two strings and return 1 if they are equal, 0 otherwise
int compararStrings(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

// Function to search for a recipe by name
void buscarReceitaPorNome(Receita** receitas, int numReceitas, char* nome) {
    int encontrada = 0;
    for (int i = 0; i < numReceitas; i++) {
        if (compararStrings(receitas[i]->nome, nome) == 1) {
            printf("Recipe found:\n");
            printf("Name: %s\n", receitas[i]->nome);
            printf("Ingredients:\n");
            for (int j = 0; j < receitas[i]->n; j++) {
                printf("%s - %d\n", receitas[i]->v[j].nome, receitas[i]->v[j].qtd);
            }
            encontrada = 1;
            break;
        }
    }

    if (encontrada == 0) {
        printf("Recipe not found!\n");
    }
}

// Function to search for recipes that use a specific ingredient
void buscarReceitasPorIngrediente(Receita** receitas, int numReceitas, char* ingrediente) {
    int encontrada = 0;
    printf("Recipes that use the ingredient %s:\n", ingrediente);
    for (int i = 0; i < numReceitas; i++) {
        for (int j = 0; j < receitas[i]->n; j++) {
            if (compararStrings(receitas[i]->v[j].nome, ingrediente) == 1) {
                printf("- %s\n", receitas[i]->nome);
                encontrada = 1;
                break;
            }
        }
    }

    if (!encontrada) {
        printf("No recipe uses the ingredient %s!\n", ingrediente);
    }
}