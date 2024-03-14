#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>

int main(void){
    int var;
    var = 1;
    int pid,mypid,status;
    printf("valor antes do fork():%d\n", var);
    pid = fork();
    if(pid != 0){
        waitpid(-1,&status,0);
        if(!WIFEXITED(status)){
           printf("child process failed\n");
        }
        printf("novo valor depois do fork():%d\n", var);


    }else{
        var = 5; // o valor não muda no processo pq estão em "contextos diferentes"
        printf("Valor antes do exit():%d\n",var);
        exit(3);
    }

    return 0;
}
