#ifndef CRIA_FUNC_H
#define CRIA_FUNC_H

typedef enum {INT_PAR,PTR_PAR}tipoValor;
typedef enum {PARAM,FIX,IND}origemValor;

typedef struct{
	tipoValor tipo_val;
	origemValor orig_val;
	union {
		int v_int;
		void *v_ptr;
	}valor;
}DescParam;

void cria_func(void* f, DescParam params[], int n, unsigned char codigo[]);

#endif
