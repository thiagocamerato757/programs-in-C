#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>

int main(void){
    int pid,mypid,status;
    pid = fork();
    if(pid != 0){
        waitpid(-1,&status,0);
        if(!WIFEXITED(status)){
           printf("child process failed\n");
        }

    }else{
        char* argv[2] = {"programaMegacomplicado",NULL}; // argv sempre termina em NULL
        int s = execve(argv[0],argv ,0);// argv[0] sempre vai ser o nome do executável do programa que nós queremos executar
        exit(3);
    }

    return 0;
}
