#include<stdio.h>
#include <unistd.h>
int main(void){
    for (int i = 0; i < 20; i++) {
        printf("hello\n");
        sleep(1);
    }
    return 0;
}