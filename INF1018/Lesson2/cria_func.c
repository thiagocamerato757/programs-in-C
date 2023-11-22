#include "cria_func.h"
#include <stdlib.h>

void* cria_func(void* f, DescParam params[], int n, unsigned char codigo[]) {
    unsigned char* p = codigo;

    // Prólogo
    // TODO: Adicione as instruções de prólogo aqui

    // Reserva espaço para variáveis locais (opcional)
    // TODO: Adicione as instruções de reserva de espaço aqui

    // Itera sobre os parâmetros
    for (int i = 0; i < n; ++i) {
        if (params[i].orig_val == IND) {
            // TODO: Adicione as instruções para carregar o valor da variável
        } else if (params[i].orig_val == FIX) {
            // TODO: Adicione as instruções para carregar o valor fixo
        }
        // TODO: Adicione instruções para tratar diferentes tipos de parâmetros
    }

    // Chamada à função original
    // TODO: Adicione as instruções para chamar a função original

    // Epílogo: desfazer registro de ativação e retornar
    // TODO: Adicione as instruções de epílogo

    // Retorna o endereço do código gerado (início do bloco de código)
    return (void*)codigo;
}
