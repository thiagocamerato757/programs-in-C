#include <unistd.h>
int main(void){
    int count = 0;
    for (int i = 0; i < 20; i++) {
        count += 1;
        sleep(1);
    }
    return 0;
}