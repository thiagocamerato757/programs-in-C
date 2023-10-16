.text
.globl add
add:
   pushq %rbp
   movq %rsp,%rbp
   subq $16,%rsp
   addl %edi,%esi
   addl %esi,%edx
   movl %edx,%eax
   leave
   ret
