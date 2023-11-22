#define MAX 4
#define MIN 2

typedef struct no t_no;

struct no {
    int ndesc;
    int chave[MAX];
    t_no *ramo[MAX + 1];
};

void imprime_intervalo(t_no *arv, int lim_inf, int lim_sup);
t_no *insere_chave(t_no *raiz, int chave);
void imprime_simetrica(t_no *raiz);