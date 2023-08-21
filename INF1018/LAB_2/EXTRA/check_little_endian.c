#include<stdio.h>

int is_little(void){
	int n = 1;
	char *bytePointer = (char *)&n;
	//se o conteúdo contido no byte menos significativo for 1, então 
	//é little-endian
	return(*bytePointer == 1);
}

int main(void){
	if(is_little()){
		printf("A memória tem organização little-endian\n");
	}
	else{
		printf("A memória não é little-endian\n");
	}
	return 0;
}
