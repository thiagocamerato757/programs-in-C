.data
nums: .int 65,-105,111,34
Sf: .string "soma = %d\n"

.text
.globl main
main:
   pushq %rbp
   movq %rsp,%rbp
   subq $16,%rsp
   movq %r12,-8(%rbp)
   movl $0,%r10d      # contador
   movl $0,%r11d      # armazena soma
   movq $nums,%r12    # guarda o vetor

   L1:
     cmpl $4,%r10d    # Compare r10 to 4
     je L2            # Jump to L2 if equal
     movq %r10,%rcx
     imull $4,%ecx
     addq (%rcx),%r12
     addl (%r12),%r11d
     addl $1, %r10d   # Incrementa  contador
     jmp L1

   L2:
     movq $Sf,%rdi     
     movl %r11d,%esi   
     xorl %eax, %eax
     call printf
     movq -8(%rbp),%r12
     movq %rbp,%rsp
     popq %rbp
     ret
     
