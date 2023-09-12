#include <stdio.h>
typedef unsigned packed_t;
int xbyte(packed_t word, int bytenum) {
  unsigned char *p = (unsigned char *)&word;
  return (int)(char)p[bytenum];
}
int main(int argc, char **argv) {
  int x;
  if (argc != 3) {
    printf ("uso: %s <word (em hexadecimal)> <bytenum>\n", argv[0]);
    exit(1);
  }

  x = xbyte(string2num(argv[1], 16), atoi(argv[2]));
  printf ("%08x  %d\n", x, x);
  return 0;
}
