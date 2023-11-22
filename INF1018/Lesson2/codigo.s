.data
string1: .string "aloaloalao"
string2: .string "lalalalalal"
.text
.globl main
main: 
pushq %rbp
movq %rsp,%rbp
subq $64,%rsp
movl $10,%edi
movl $20,%esi
movq $string1,%rdi
movq $string2,%rsi
movl $15,-4(%rbp)
movl $19,-8(%rbp)
movq string1,-16(%rbp)
movq string2,-32(%rbp)
leaq -4(%rbp),%r10
leave
ret
