.data
nums: .byte 10, -21, -30, 45
Sf: .string "%d\n"    # string de formato para printf

.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)

    movl $0, %ebx         # ebx = 0
    movq $nums, %r12      # r12 = &nums

L1:
    cmpl $4, %ebx         # if (ebx == 4) ?
    je L2                 # goto L2

    movzbl (%r12), %eax   # Load a zero-extended byte from r12 to eax
    movsbq %al, %rax      # Sign-extend AL to RAX

    movq $Sf, %rdi        # primeiro parâmetro (ponteiro)
    movq %rax, %rsi       # segundo parâmetro (inteiro)
    call printf           # chama a função da biblioteca

    addl $1, %ebx         # ebx += 1
    incq %r12             # r12 += 1 (avança 1 byte)
    jmp L1                # goto L1

L2:
    movq $0, %rax         # rax = 0 (valor de retorno)
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    leave
    ret

