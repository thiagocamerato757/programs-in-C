

//includes 
#include<stdio.h>

//function prototypes
long long int ackermann(long long int m, long long int n);

//main function 
int main(void){
    //variables
    long long int m;
    long long int n;
    long long int result;

    //execution
    printf("Digite dois números pra usarmos na funçãoa de Ackermann \n");
    printf("primeiro número:");
    scanf("%lld",&m);  
    printf("segundo número:");
    scanf("%lld",&n);  
    result = ackermann(m, n);
    printf("resultado : %lld\n",result);

    return 0;
}
long long int ackermann(long long int m, long long int n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    } else {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}