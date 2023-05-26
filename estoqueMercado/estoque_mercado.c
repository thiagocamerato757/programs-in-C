//includes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//creating simbolic variabes 
#define MAX_NOME 15
#define MAX_PRODUTOS 10
#define MAX_PEDIDOS 8

//structed data
typedef struct {
    int codigo;
    char nome[MAX_NOME + 1];
    float preco;
    int quantidade;
} Produto;

typedef struct {
    int codigo;
    int quantidade;
} Pedido;

//function prototypes
void preencherProdutos(Produto** produtos);
void lerPedidos(Produto** produtos, Pedido* pedidos);


//main function
int main(void){
    //variables
    Produto* produtos[MAX_PRODUTOS];
    Pedido pedidos[MAX_PEDIDOS];

    //execution
    preencherProdutos(produtos);
    lerPedidos(produtos, pedidos);

    //dealocating memory
 int i;
    for (i = 0; i < MAX_PRODUTOS; i++) {
        free(produtos[i]);
    }
    
    return 0;
}

void preencherProdutos(Produto** produtos) {
    int i;
    for (i = 0; i < MAX_PRODUTOS; i++) {
        Produto* produto = malloc(sizeof(Produto));
        if(produto == NULL){
            fprintf(stderr,"Erro ao alocar memória do %d produto!\n",i);
            exit(1);
        }
        
        printf("Produto %d:\n", i + 1);
        
        printf("Código: ");
        scanf("%d", &(produto->codigo));
        
        printf("Nome: ");
        scanf(" %s", produto->nome);
        
        printf("Preço: ");
        scanf("%f", &(produto->preco));
        
        printf("Quantidade: ");
        scanf("%d", &(produto->quantidade));
        
        produtos[i] = produto;
        printf("\n");
    }
}
void lerPedidos(Produto** produtos, Pedido* pedidos) {
    int i;
    for (i = 0; i < MAX_PEDIDOS; i++) {
        Pedido pedido;
        
        printf("Pedido %d:\n", i + 1);
        
        printf("Código do produto: ");
        scanf("%d", &(pedido.codigo));
        
        printf("Quantidade: ");
        scanf("%d", &(pedido.quantidade));
        
        int j;
        int encontrado = 0;
        for (j = 0; j < MAX_PRODUTOS; j++) {
            if (produtos[j]->codigo == pedido.codigo) {
                encontrado = 1;
                if (produtos[j]->quantidade >= pedido.quantidade) {
                    produtos[j]->quantidade -= pedido.quantidade;
                    printf("Pedido atendido.\n\n");
                } else {
                    printf("Estoque insuficiente.\n\n");
                }
                break;
            }
        }
        
        if (!encontrado) {
            printf("Produto inexistente.\n\n");
        }
        
        pedidos[i] = pedido;
    }
}
