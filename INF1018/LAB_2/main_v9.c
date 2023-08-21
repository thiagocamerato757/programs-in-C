#include<ctype.h>
#include<stdio.h>

int char_to_digit(char c) {
  if (isdigit(c))
    return c - '0';
  if ('a' <= c && c <= 'z')
    return c - 'a' + 10;
  return -1; // Invalid character
}

int string2num(char *s, int base) {
  int a = 0;
  for (; *s; s++) {
    int digit = char_to_digit(*s);
    if (digit < 0 || digit >= base)
      return -1; // Invalid character or digit for base
    a = a * base + digit;
  }
  return a;
}

int main(void){
	
	printf("%d\n", string2num("1a", 16));
	printf("%d\n", string2num("a09b", 16));
	printf("%d\n", string2num("z09b", 36));
	return 0;
}
