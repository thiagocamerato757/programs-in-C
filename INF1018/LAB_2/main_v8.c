#include<ctype.h>
#include<stdio.h>

int string2num(char *s, int base) {
  int a = 0;
  for (; *s; s++) {
    int digit;
    if (isdigit(*s))
      digit = *s - '0';
    else
      return -1; // Invalid character
    if (digit >= base)
      return -1; // Invalid digit for base
    a = a * base + digit;
  }
  return a;
}

int main(void){
	
       	printf("%d\n", string2num("777", 8));
	printf("%d\n", string2num("777", 10));
	return 0;
}
