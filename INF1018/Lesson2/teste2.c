#include <stdio.h>
#include "cria_func.h"
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_START(P) ((intptr_t)(P)&~(pagesize-1))
#define PAGE_END(P) (((intptr_t)(P)+pagesize-1)&~(pagesize-1))

/*
 * The execpage() function shall change the specified memory pages
 * permissions into executable.
 *
 * void *ptr  = pointer to start of memory buff
 * size_t len = memory buff size in bytes
 *
 * The function returns 0 if successful and -1 if any error is encountered.
 * errono may be used to diagnose the error.
 */
int execpage(void *ptr, size_t len) {
    int ret;

    const long pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1)
        return -1;

    ret = mprotect((void *)PAGE_START(ptr),
                   PAGE_END((intptr_t)ptr + len) - PAGE_START(ptr),
                   PROT_READ | PROT_WRITE | PROT_EXEC);
    if (ret == -1)
        return -1;

    return 0;
}

#undef PAGE_START
#undef PAGE_END

typedef int (*func_ptr)();

unsigned char codigo[500]; // Declaração global

int mult(int x, int y) {
    return x * y;
}

int main(void) {
    DescParam params[2];
    func_ptr f_mult;
    int i;

    params[0].tipo_val = INT_PAR; /* a nova função passa para mult um valor inteiro */
    params[0].orig_val = IND;     /* que é o valor corrente da variável i */
    params[0].valor.v_ptr = &i;
    //printf("%p",(int*)params[0].valor.v_ptr);

    params[1].tipo_val = INT_PAR; /* o segundo argumento passado para mult é a constante 10 */
    params[1].orig_val = FIX;
    params[1].valor.v_int = 10;

    cria_func(mult, params, 2, codigo);

    // Garante que as páginas de código são executáveis
    if (execpage(codigo, sizeof(codigo)) == -1) {
        perror("execpage");
        return 1;
    }
    f_mult = (func_ptr)codigo;
    for (i = 1; i <= 10; i++) {
      printf("%d\n", f_mult()); /* a nova função não recebe argumentos */
    }

    return 0;
}
