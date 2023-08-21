#include"main.h"

int main(void){
	char c = 'a';
 	 dump(&c, sizeof(c));
 	 c = 97;
 	 dump(&c, sizeof(c));
	 return 0;
}
