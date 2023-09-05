#include <stdio.h>

unsigned char rotate_left(unsigned char x, int n) {
    unsigned char b1, b2;
    n %= 9; // Ensure n is within the range [0, 8]

    b1 = (x << n) | (x >> (8 - n));
    return b1;
}

int main(void) {
    unsigned char end = 0x61;
    int numbits;

    printf("Enter the number of bits to rotate left: ");
    scanf("%d", &numbits);

    unsigned char rotated_value = rotate_left(end, numbits);
    printf("A left rotation of %d bits results in the value 0x%x.\n", numbits, rotated_value);

    return 0;
}
