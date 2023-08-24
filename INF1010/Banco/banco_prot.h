//structed data
struct conta
{
    int id;
    float saldo;
};
typedef struct conta Conta;
//function prototypes
Conta criaConta(void);
void deposita(Conta *ct,float numb);
void saque(Conta *ct,float numb);
void imprimeSaldo(Conta ct);