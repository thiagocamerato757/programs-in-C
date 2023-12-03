//Thiago Pereira Camerato 2212580
#include <stdio.h>
#include <stdlib.h>
#include "cria_func.h"

void preenche(unsigned char* codigo, char opcode,int* index) {
    codigo[(*index)] = opcode;
    (*index)++;
}


void addB(unsigned char *bytes, int tam, unsigned char *codigo, int *index){
    for (int i = 0; i < tam; i++){
       preenche(codigo, bytes[i], index);
    }
}


void reorganizaParam(unsigned char *codigo, int nParam, int i, int *index){
    if (nParam < i){
        unsigned char *moveParam;
        if (nParam == 0 && i == 1){
            unsigned char temp[] = { 0x4c, 0x89, 0xc6 }; //mov %r8, %rsi
            moveParam = temp;
        }else if (nParam == 0 && i == 2){
            unsigned char temp[] = { 0x4c, 0x89, 0xca }; //mov %r9, %rdx
            moveParam = temp;
        }else if (nParam == 1 && i == 2){
            unsigned char temp[] = { 0x4c, 0x89, 0xd2 }; //mov %r10, %rdx
            moveParam = temp;
        }
        addB(moveParam, 3, codigo, index);
    }
}


void cria_func(void* f, DescParam params[], int n, unsigned char codigo[]){
    if (n < 1 || n > 3){
        printf("a quantidade de parametros passado nao e valida, o minimo e 1 e o maximo e 3");
        exit(1);
    }
    
    codigo[0] = 0x55; //pushq %rbp
    codigo[1] = 0x48; codigo[2] = 0x89; codigo[3] = 0xe5;  //movq% rsp, % rbp
    codigo[4] = 0x48 ;codigo[5] = 0x83; codigo[6] = 0xec; codigo[7] = 0x20; //subq $32, % rsp
    

    // movendo o endereço da função para o %rax
    codigo[8] = 0x48; /* move o endereço da funcao para o %rax com movabsq*/
    codigo[9] = 0xb8; 
    *((long*)(codigo + 10)) =  (long)f;
    //index para percorrer o codigo
    int index = 18;
    long pFix;
    unsigned char byte;
    int nParam = 0;


    // 0x49, 0x89, 0xf8, //movq %rdi, %r8
    codigo[index++] =  0x49;
    codigo[index++] =  0x89;
    codigo[index++] =  0xf8;
    
    //0x49, 0x89, 0xf1, //movq %rdi, %r9
    codigo[index++] =  0x49;
    codigo[index++] =  0x89;
    codigo[index++] =  0xf1;
    
    //0x49, 0x89, 0xd2 //movq %rdi, %r10
    codigo[index++] =  0x49;
    codigo[index++] =  0x89;
    codigo[index++] =  0xd2;
    
    
    
    for (int i = 0; i < n; ++i){
	    DescParam param = params[i];
            if (param.orig_val == PARAM){
                reorganizaParam(codigo, nParam, i, &index);
                nParam++;
            }else if (params[i].orig_val == FIX){
                //o parâmetro deve ser amarrado a um valor constante, fornecido no campo valor
                if (params[i].tipo_val == INT_PAR){
                    if (i == 0){
                        codigo[index++] = 0xbf;
                        *((int*)(codigo + (index))) = params[i].valor.v_int; //preenche os proximos 4 bytes com o valor
                        index += 4;

                    }else if (i == 1){
                        codigo[index++] = 0xbe;
                        *((int*)(codigo + (index))) =  params[i].valor.v_int;//preenche os proximos 4 bytes com o valor
                        index += 4;

                    }else if (i == 2){
                        codigo[index++] = 0xba;
                        *((int*)(codigo + (index))) = params[i].valor.v_int; //preenche os proximos 4 bytes com o valor
                        index += 4;
                    }
            }else if (params[i].tipo_val == PTR_PAR){
                codigo[index++] = 0x48;
                codigo[index++] = 0xbf;
                //procurar as ocorrencias e substituir pelos fixos como fazer em assembly passando a constante?
                if (i == 0){
                   *((long*)(codigo + index)) = (long)params[i].valor.v_ptr;
                   index+=8;
                   
                }else if (i == 1){
                   *((int**)(codigo + index)) = (int*)params[i].valor.v_ptr;
                   index+=8;
                    
                }else if (i == 2){ 
                   *((long*)(codigo + index)) = (long)params[i].valor.v_ptr;
                   index+=8;
                    
                }
            }
        }else if (params[i].orig_val == IND) {
                pFix = (long)params[i].valor.v_ptr;
                preenche(codigo, 0x48, &index); 
                preenche(codigo, 0xb9, &index);  
                
                for (int i = 0; i < 8; i++) {
                        // Extrai o byte mais à direita de pFix
                        byte = (unsigned char)(pFix & 0xFF);
                        // Insere o byte no vetor codigo
                        preenche(codigo, byte, &index);
                        // Desloca pFix para a direita por 8 bits para obter o próximo byte
                        pFix >>= 8;
                }
                // Instrução de carregamento dependendo do índice i
                if (i == 2) {
                        preenche(codigo, 0x48, &index);
                        preenche(codigo, 0x8b, &index);
                        preenche(codigo, 0x11, &index);
                } else if (i == 1) {
                        preenche(codigo, 0x48, &index);
                        preenche(codigo, 0x8b, &index);
                        preenche(codigo, 0x31, &index);
                } else {
                       preenche(codigo, 0x48, &index);
                        preenche(codigo, 0x8b, &index);
                        preenche(codigo, 0x39, &index);
                }
            }
    }

    codigo[index++] = 0xff;
    codigo[index++] = 0xd0;  // call *%rax

    codigo[index++] = 0xc9;
    codigo[index++] = 0xc3;

}
