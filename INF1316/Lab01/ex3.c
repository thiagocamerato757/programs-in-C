#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>

int cmpfunc(const void* a, const void* b){
    return (*(int*)a-*(int*)b);
}

int main(void){
    int vet[10] = {1,7,5,6,0,2,3,9,8,10};
    printf("antes do filho\n");
    for(int i = 0; i < 10; i++){
        printf("%d-",vet[i]);
    }
    printf("\n");
    int pid,mypid,status;
    pid = fork();
    if(pid != 0){
        waitpid(-1,&status,0);
        if(!WIFEXITED(status)){
           printf("child process failed\n");
        }
        printf("depois do filho\n");
        for(int i = 0; i < 10; i++){
            printf("%d-",vet[i]);
        }
        printf("\n");


    }else{
        qsort(vet,10,sizeof(int),cmpfunc);
        printf("no filho\n");
        for(int i = 0; i < 10; i++){
            printf("%d-",vet[i]);
        }
        printf("\n");
        exit(3);
    }

    return 0;
}
