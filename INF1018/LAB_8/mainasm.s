.data
nums: .int 3, -5, 7, 8, -2
s1:   .string "%d\n"

.text
.globl main

main:
  # Prologue
  pushq %rbp
  movq  %rsp, %rbp
  subq  $16, %rsp
  movq  %rbx, -8(%rbp)
  movq  %r12, -16(%rbp)

  # Initialize loop counter
  movl $0, %ebx
  movq $nums, %r12

L1:
  cmpl $5, %ebx
  je L2

  # Load the current integer from the array
  movl (%r12), %edi

  # Call the 'filtro' function
  movl $1, %esi
  call filtro

  # Prepare for printf
  movq $s1, %rdi
  movq %rax,%rsi
  movl $0, %eax
  call printf

  # Update loop counter and array pointer
  incl %ebx
  addq $4, %r12
  jmp L1

L2:
  # Finalization
  xorl %eax,%eax
  movq -8(%rbp), %rbx
  movq -16(%rbp), %r12
  leave
  ret

.globl filtro

filtro:
  pushq %rbp
  movq %rsp, %rbp
  cmpl %esi,%edi
  jle L3

  # If edi > esi, return edi
  movl %edi, %eax
  leave
  ret

L3:
  # If edi <= esi, return 0
  movl $0, %eax
  leave
  ret

