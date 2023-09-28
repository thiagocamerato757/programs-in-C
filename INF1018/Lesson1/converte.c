#include "converte.h"
#include <stdio.h>

int utf2varint(FILE *arq_entrada, FILE *arq_saida) {
    int unicodeValue;

    while (fscanf(arq_entrada, "%d", &unicodeValue) == 1) {
        if (unicodeValue >= 0 && unicodeValue <= 0x10FFFF) {
            char buffer[5];
            int byteCount = 0;

            if (unicodeValue <= 0x7F) {
                buffer[0] = (char)unicodeValue;
                byteCount = 1;
            } else if (unicodeValue <= 0x7FF) {
                buffer[0] = (char)(0xC0 | ((unicodeValue >> 6) & 0x1F));
                buffer[1] = (char)(0x80 | (unicodeValue & 0x3F));
                byteCount = 2;
            } else if (unicodeValue <= 0xFFFF) {
                buffer[0] = (char)(0xE0 | ((unicodeValue >> 12) & 0x0F));
                buffer[1] = (char)(0x80 | ((unicodeValue >> 6) & 0x3F));
                buffer[2] = (char)(0x80 | (unicodeValue & 0x3F));
                byteCount = 3;
            } else if (unicodeValue <= 0x10FFFF) {
                buffer[0] = (char)(0xF0 | ((unicodeValue >> 18) & 0x07));
                buffer[1] = (char)(0x80 | ((unicodeValue >> 12) & 0x3F));
                buffer[2] = (char)(0x80 | ((unicodeValue >> 6) & 0x3F));
                buffer[3] = (char)(0x80 | (unicodeValue & 0x3F));
                byteCount = 4;
            }

            fwrite(buffer, 1, byteCount, arq_saida);
        } else {
            fprintf(stderr, "Valor Unicode fora do intervalo válido: %d\n", unicodeValue);
            return -1;
        }
    }

    return 0;
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida) {
    char buffer[5];
    int bytesRead;

    while ((bytesRead = fread(buffer, 1, 5, arq_entrada)) > 0) {
        int unicodeValue = 0;

        if ((buffer[0] & 0x80) == 0) {
            unicodeValue = buffer[0];
        } else if ((buffer[0] & 0xE0) == 0xC0) {
            unicodeValue = (buffer[0] & 0x1F) << 6;
            unicodeValue |= (buffer[1] & 0x3F);
        } else if ((buffer[0] & 0xF0) == 0xE0) {
            unicodeValue = (buffer[0] & 0x0F) << 12;
            unicodeValue |= (buffer[1] & 0x3F) << 6;
            unicodeValue |= (buffer[2] & 0x3F);
        } else if ((buffer[0] & 0xF8) == 0xF0) {
            unicodeValue = (buffer[0] & 0x07) << 18;
            unicodeValue |= (buffer[1] & 0x3F) << 12;
            unicodeValue |= (buffer[2] & 0x3F) << 6;
            unicodeValue |= (buffer[3] & 0x3F);
        } else {
            fprintf(stderr, "Varint inválido encontrado no arquivo.\n");
            return -1;
        }

        fprintf(arq_saida, "%d ", unicodeValue);
    }

    return 0;
}
