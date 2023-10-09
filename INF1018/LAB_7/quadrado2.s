.data
Sf: .string "%d\n"

.text
.globl main
main:
  pushq %rbp
  movq %rsp, %rbp
  subq $16, %rsp
  movl %r13d, -8(%rbp)
  movl $1, %r10d
L1:
  movl %r10d, -4(%rbp) #salva o valor do contador
  cmpl $11, %r10d
  je L2
  movl  %r10d,%r13d
  imull %r13d,%r13d
  movl %r13d, %esi
  movq $Sf, %rdi
  call printf
  movl -4(%rbp), %r10d #devolve o valor salvo anteriormente
  addl $1, %r10d
  jmp L1

L2:
  xorl %eax, %eax
  movl -8(%rbp), %r13d
  movq %rbp,%rsp
  popq %rbp
  ret


