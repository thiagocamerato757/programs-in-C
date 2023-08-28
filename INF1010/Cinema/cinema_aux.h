//structed data
struct Pessoa
{
    int id;
    int idade;
    struct Pessoa *prox;
};
typedef struct Pessoa pessoa;

struct Fila
{
    pessoa *inicio;
    pessoa *fim;
};
typedef struct Fila fila;

fila *criaFila(void);
void adiciona(fila *fl, int info1, int info2);
void imprimePassagem(fila *fl, fila *fl2);
