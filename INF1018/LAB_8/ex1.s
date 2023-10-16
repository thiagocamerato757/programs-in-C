.data
s1: .string "ls -ls"

.text
.globl main
main:
  # Prologue
  pushq %rbp
  movq %rsp, %rbp

  movq $s1, %rdi        
  call system

  leave
  ret

