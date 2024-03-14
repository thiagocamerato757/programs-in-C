#include<unistd.h>
int main(void){
    char* argv[3] = {"/bin/echo","HELLO WORLD",NULL};
    execve(argv[0],argv,0);

    return 0;
}