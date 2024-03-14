#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(void){
    int pid,mypid,status;
    pid = fork();
    if(pid != 0){
        mypid = getpid();
        printf("Father PID: %d\n", mypid);
        waitpid(-1, &status, 0);
        if(!WIFEXITED(status)){
            printf("child process failed\n");
        }
    }else{
        mypid = getpid();
        printf("Child PID: %d\n", mypid);
        exit(3);
    }

    return 0;
}