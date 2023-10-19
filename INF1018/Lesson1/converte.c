//Thiago Pereira Camerato 2212580
#include "converte.h"
#include <stdio.h>

// Function to convert UTF-8 to varint
int utf2varint(FILE *arq_entrada, FILE *arq_saida) {
    // Check if the input and output files are valid
    if (arq_entrada == NULL || arq_saida == NULL) {
        fprintf(stderr, "Error opening input/output files.\n");
        return -1;
    }

    int c;                  // Current character read from input
    unsigned int codepoint = 0;  // Unicode code point being constructed

    while ((c = fgetc(arq_entrada)) != EOF) {
        // Determine the number of bytes used to represent the character
        if ((c & 0x80) == 0) {
            codepoint = c;
        } else if ((c & 0xE0) == 0xC0) {
            codepoint = c & 0x1F;
            c = fgetc(arq_entrada);
            if (c == EOF || (c & 0xC0) != 0x80) {
                fprintf(stderr, "UTF-8 encoding error.\n");
                return -1;
            }
            codepoint = (codepoint << 6) | (c & 0x3F);
        } else if ((c & 0xF0) == 0xE0) {
            codepoint = c & 0x0F;
            for (int i = 0; i < 2; i++) {
                c = fgetc(arq_entrada);
                if (c == EOF || (c & 0xC0) != 0x80) {
                    fprintf(stderr, "UTF-8 encoding error.\n");
                    return -1;
                }
                codepoint = (codepoint << 6) | (c & 0x3F);
            }
        } else if ((c & 0xF8) == 0xF0) {
            codepoint = c & 0x07;
            for (int i = 0; i < 3; i++) {
                c = fgetc(arq_entrada);
                if (c == EOF || (c & 0xC0) != 0x80) {
                    fprintf(stderr, "UTF-8 encoding error.\n");
                    return -1;
                }
                codepoint = (codepoint << 6) | (c & 0x3F);
            }
        } else {
            fprintf(stderr, "UTF-8 encoding error.\n");
            return -1;
        }

        // Write the codepoint as a varint to the output file
        while (codepoint > 0) {
            int byte = (codepoint & 0x7F) | 0x80;
            if (codepoint <= 0x7F) {
                byte = codepoint;
            }
            if (fputc(byte, arq_saida) == EOF) {
                fprintf(stderr, "Error writing to the output file.\n");
                return -1;
            }
            codepoint >>= 7;
        }
    }

    return 0;
}

// Function to convert varint to UTF-8
int varint2utf(FILE *arq_entrada, FILE *arq_saida) {
    // Check if the input and output files are valid
    if (arq_entrada == NULL || arq_saida == NULL) {
        fprintf(stderr, "Error opening input/output files.\n");
        return -1;
    }

    unsigned int codepoint = 0; // Unicode code point being constructed
    int shift = 0;              // Number of bits shifted in

    int c;
    while ((c = fgetc(arq_entrada)) != EOF) {
        codepoint |= (c & 0x7F) << shift;
        shift += 7;

        if ((c & 0x80) == 0) {
            // Write the codepoint in UTF-8 format to the output file
            if (codepoint < 0x80) {
                if (fputc(codepoint, arq_saida) == EOF) {
                    fprintf(stderr, "Error writing to the output file.\n");
                    return -1;
                }
            } else if (codepoint < 0x800) {
                if (fputc(0xC0 | (codepoint >> 6), arq_saida) == EOF) {
                    fprintf(stderr, "Error writing to the output file.\n");
                    return -1;
                }
                if (fputc(0x80 | (codepoint & 0x3F), arq_saida) == EOF) {
                    fprintf(stderr, "Error writing to the output file.\n");
                    return -1;
                }
            } else if (codepoint < 0x10000) {
                if (fputc(0xE0 | (codepoint >> 12), arq_saida) == EOF) {
                    fprintf(stderr, "Error writing to the output file.\n");
                    return -1;
                }
                if (fputc(0x80 | ((codepoint >> 6) & 0x3F), arq_saida) == EOF) {
                    fprintf(stderr, "Error writing to the output file.\n");
                    return -1;
                }
                if (fputc(0x80 | (codepoint & 0x3F), arq_saida) == EOF) {
                    fprintf(stderr, "Error writing to the output file.\n");
                    return -1;
                }
            } else {
                if (fputc(0xF0 | (codepoint >> 18), arq_saida) == EOF) {
                    fprintf(stderr, "Error writing to the output file.\n");
                    return -1;
                }
                if (fputc(0x80 | ((codepoint >> 12) & 0x3F), arq_saida) == EOF) {
                    fprintf(stderr, "Error writing to the output file.\n");
                    return -1;
                }
                if (fputc(0x80 | ((codepoint >> 6) & 0x3F), arq_saida) == EOF) {
                    fprintf(stderr, "Error writing to the output file.\n");
                    return -1;
                }
                if (fputc(0x80 | (codepoint & 0x3F), arq_saida) == EOF) {
                    fprintf(stderr, "Error writing to the output file.\n");
                    return -1;
                }
            }

            codepoint = 0;
            shift = 0;
        }
    }

    return 0;
}

// Function to open a file with the specified name and mode
FILE *abreArq(char *name, char *mode) {
    // Attempt to open the file with the given name and mode
    FILE *file = fopen(name, mode);

    // Check if the file was successfully opened
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s in mode %s\n", name, mode);
    }

    return file;
}
