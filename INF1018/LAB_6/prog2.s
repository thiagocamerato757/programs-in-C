/*
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  int sum = 0;
  for (i = 0, p = nums; i != 4; i++, p++)
    sum += *p;
  printf("%d\n", sum);
  return 0;
}
*/

.data
nums : .int 10,-21,-30,45
Sf : .string "%d\n"

.text
.globl main

main :
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    %rbx, -8(%rbp)
    movq    %r12, -16(%rbp)

    movl  $0, %ebx  /* ebx = 0; */
    movq  $nums, %r12  /* r12 = &nums */
    movl $0, %edx /* %edx = 0 */

L1:
    cmpl  $4, %ebx  /* if (ebx == 4) ? */
    je  L2          /* goto L2 */
    
    movl  (%r12), %eax    /* eax = *r12 */
    addl  %eax,%edx       /*edx += eax */
    
    addl  $1, %ebx  /* ebx += 1; */
    addq  $4, %r12  /* r12 += 4; */
    jmp  L1         /* goto L1; */
L2:

    movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
    movl    %edx, %esi   /* segundo parametro  (inteiro) */
    call  printf       /* chama a funcao da biblioteca */
    movq  $0, %rax  /* rax = 0  (valor de retorno) */
    movq  -8(%rbp), %rbx
    movq  -16(%rbp), %r12
    leave
    ret
