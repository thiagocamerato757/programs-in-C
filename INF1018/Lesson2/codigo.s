.text
.globl main
main:
    pushq %rbp
    movq  %rsp,%rbp
    movabsq 0xaa,%rax
    call *%rax
    leave
    ret

