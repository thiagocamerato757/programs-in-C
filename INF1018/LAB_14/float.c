#include<stdio.h>
#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))
#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)
float float2(float f);
float int2float(int i);
typedef union { 
  float f;
  unsigned int i;
 } U;
int main(void){
	float f1;
	printf("digite um float:\n");
	scanf("%f",&f1);
	printf("o dobro dele eh : %f\n",float2(f1));
	int i;

  	 printf("\n******** int2float ****************\n");
   	i = 0;
   	printf(" %d -> %+10.4f\n", i, int2float(i));
   	i = 1;
   	printf(" %d -> %+10.4f\n", i, int2float(i));
   	i = -1;
   	printf(" %d -> %10.4f\n", i, int2float(i));
   	i = 0x7fffffff;
   	printf(" %d -> %+10.4f\n", i, int2float(i));
   	i = -i;
   	printf(" %d -> %+10.4f\n", i, int2float(i));
   	i = 12345;
   	printf(" %d -> %+10.4f\n", i, int2float(i));
   	i = -12345;
   	printf(" %d -> %+10.4f\n", i, int2float(i));
   
	return 0;
}
float float2(float f){
	U u;
	unsigned int u1;
	u.f = f;
	u1 = u.i;
        u.i = makefloat(getsig(u1),(getexp(u1)|1),getfrac(u1));
	f = u.f;
	return u.f;
}

float int2float(int i){
	if(i==0) return 0.0;
	else{
		return makefloat(getsig(i),getexp(i),getfrac(i));
	}
}
	
