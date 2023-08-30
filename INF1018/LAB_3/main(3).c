#include<stdio.h>

unsigned char switch_byte(unsigned char x){
	return (x >> 4) | (x<<4);
}

int main(void){
	 printf("%02x becomes %02x after switching bytes\n", 0xAB, switch_byte(0xAB));
	 return 0;
}

