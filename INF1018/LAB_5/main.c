#include<stdio.h>
struct X{
	int a;
	short b;
	int c;
}x = {0xa1a2a3a4,0xb1b2,0xc1c2c3c4};
void dump(void*p, int n){
	unsigned char *p1 = p;
	while(n--){
		printf("%p - %02x\n",p1,*p1);
		p1++;
	}
}

int main(void){
	int i,j;
	short a[2][3];
	int b[2];

	for(i = 0; i < 2;i++){
		b[i] = i;
		for(j = 0; j < 3;j++){
			a[i][j] = 3*i+j;
		}
	}
	printf("b:\n");
	dump(b,sizeof(b));
	printf("a:\n");
	dump(a,sizeof(a));
	printf("x:\n");
	dump(&x,sizeof(x));

	return 0;
}

