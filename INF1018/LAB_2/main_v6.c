#include"main.h"

int main(void){
	
	char A = 'A';
	 dump(&A, sizeof(A));

	 char space = ' ';
	 dump(&space, sizeof(space));

	 char newline = '\n';
	 dump(&newline, sizeof(newline));

	 char dollar = '$';
	 dump(&dollar, sizeof(dollar));

	 return 0;
}
