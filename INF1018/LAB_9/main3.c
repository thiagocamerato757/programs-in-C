void foo(int a[], int n);

#include<stdio.h>
int main() {
    int a[] = {1, 2, 0, 3, 4, 0, 0, 5};
    int n = 8;
    
    foo(a, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}

