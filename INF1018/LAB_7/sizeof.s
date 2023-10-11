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
   
   movq $nums,%r12 #array
   movl $0,%r10d #counter
   movl $0,%r11d #sum
   
  L1:
      cmpl $4,%r10d
      jge L2
      movl %r10d, %ecx
      movq %r12, %rdx #move to an aux in orden to mantain original address
      shl $2 ,%ecx
      addq %rcx,%rdx
      addl (%rdx),%r11d
      incl %r10d
      jmp L1
   L2:
      movl $0, %eax
      movq $Sf , %rdi
      movl %r11d, %esi
      call printf
    
     
      xorl %eax,%eax
      movq -8(%rbp),%r12
      movq %rbp,%rsp
      popq %rbp
      ret
     
