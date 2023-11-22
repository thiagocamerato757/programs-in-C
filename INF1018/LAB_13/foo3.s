.text
.globl foo
foo:
pushq %rbp
movq  %rsp,%rbp
jmp add
leave
ret
