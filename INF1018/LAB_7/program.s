.data
S2: .byte 65,108,111,32,123,103,97,108,101,114,97,125,33,0
Sf: .string "%c"
Sf2: .string "\n"

.text
.globl main

main:
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)  /* guarda rbx */
  movq    %r12, -16(%rbp)  /* guarda r12 */
  movq  $S2, %r12  /* r12 = &S2 */

L1:
  cmpb  $0, (%r12)  /* if (*pc == 0) ? */
  je  L2          /* goto L2 */
  movsbl (%r12),%eax
  cmpl $123,%eax
  je L3
  cmpl $125,%eax
  je L3 
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  movl  $0, %eax
  call  printf       /* chama a funcao da biblioteca */
  addq $1,%r12
  jmp L1
L2:
  movq  $Sf2, %rdi    /* primeiro parametro (ponteiro)*/
  movl  $0, %eax
  call  printf 
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -16(%rbp), %r12 /* recupera r12 */
  movq  -8(%rbp), %rbx  /* recupera rbx */
  leave
  ret
L3:
  addq $1,%r12
  jmp L1
          
