#include<stdio.h>

int main(void) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    for (int i = 0; i < 10; i++) {
        array[i] = array[i] * array[i];
        printf("%d\n", array[i]);
    }

    return 0;
}

