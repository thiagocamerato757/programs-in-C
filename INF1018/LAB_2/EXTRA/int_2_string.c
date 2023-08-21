#include <stdio.h>

char digit_to_char(int digit) {
    if (digit >= 0 && digit <= 9)
        return '0' + digit;
    else if (digit >= 10 && digit <= 35)
        return 'a' + (digit - 10);
    return '\0';
}

void num2string(char *s, int num, int base) {
    if (base < 2 || base > 36) {
        *s = '\0'; // Base inválida
        return;
    }

    int index = 0;

    if (num == 0) {
        s[index++] = '0';
        s[index] = '\0';
        return;
    }

    if (num < 0 && base == 10) {
        s[index++] = '-';
        num = -num;
    }

    char temp[100]; // Usamos um buffer temporário para armazenar os dígitos
    int temp_index = 0;

    while (num > 0) {
        int remainder = num % base;
        temp[temp_index++] = digit_to_char(remainder);
        num /= base;
    }

    if (s[0] == '-') {
        temp[temp_index++] = '-';
    }

    // Copia os dígitos do buffer temporário para o buffer final em ordem reversa
    for (int i = temp_index - 1; i >= 0; i--) {
        s[index++] = temp[i];
    }

    s[index] = '\0'; // Finaliza a string
}

int main(void) {
    char buffer[100];

    num2string(buffer, 777, 8);
    printf("777 in base 8: %s\n", buffer);

    num2string(buffer, 777, 10);
    printf("777 in base 10: %s\n", buffer);

    num2string(buffer, 1688, 16);
    printf("1688 in base 16: %s\n", buffer);

    return 0;
}

