#include "converte.h"

#include <stdio.h>
#include "converte.h"

int utf2varint(FILE *arq_entrada, FILE *arq_saida) {
    int codepoint;
    while ((codepoint = fgetc(arq_entrada)) != EOF) {
        if (codepoint < 128) {
            fputc(codepoint, arq_saida);
        } else {
            int remaining_bytes = 0;
            if (codepoint < 224) {
                remaining_bytes = 1;
            } else if (codepoint < 240) {
                remaining_bytes = 2;
            } else {
                remaining_bytes = 3;
            }
            int varint = codepoint;
            for (int i = 0; i < remaining_bytes; i++) {
                codepoint = fgetc(arq_entrada);
                varint = (varint << 8) | codepoint;
            }
            fwrite(&varint, 1, 4, arq_saida);
        }
    }
    return 0;
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida) {
    unsigned char varint[4];
    while (fread(varint, 4, 1, arq_entrada) == 1) {
        unsigned int codepoint = (varint[0] << 24) | (varint[1] << 16) | (varint[2] << 8) | varint[3];
        if (codepoint < 128) {
            fputc(codepoint, arq_saida);
        } else {
            int num_bytes;
            if (codepoint < 2048) {
                num_bytes = 2;
            } else if (codepoint < 65536) {
                num_bytes = 3;
            } else {
                num_bytes = 4;
            }
            for (int i = num_bytes - 1; i > 0; i--) {
                unsigned char byte = 0x80 | (codepoint & 0x3F);
                codepoint >>= 6;
                fputc(byte, arq_saida);
            }
            unsigned char first_byte = (0xFF << (8 - num_bytes)) | codepoint;
            fputc(first_byte, arq_saida);
        }
    }
    return 0;
}




FILE *abreArq(char*name,char*mode){
    return fopen(name,mode);
}