#include<stdio.h>

int add (int x) {
  return x+1;
}

typedef int (*funcp) (int x);

int main(void){
unsigned char codigo[] = {0x55,0xe8,0xc9,0xc3};
        funcp f = (funcp)codigo;
       //int i = (*f)(10);
	funcp a =(funcp)add;
        printf("%d\n",*a);
        return 0;
}

