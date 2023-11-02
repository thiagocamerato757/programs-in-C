#include<stdio.h>

typedef int (*funcp) (int x);

int main(void){
unsigned char codigo[] = {0x55,0x48,0x89,0xe5,0xff,0xc7,0x48,0x89,0xf8,0xc9,0xc3};
	funcp f = (funcp)codigo;
	int i = (*f)(10);
	printf("%d\n",i);
	return 0;
}


