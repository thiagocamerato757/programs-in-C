.data

nums: .int 10,-21,-30,45
Sf: .string "%d\n"

.text
.globl main
main:
	pushq 	%rbp
	movq	%rsp,%rbp
	subq	$16,%rsp
	movq	%rbx,-8(%rbp)
	movq	%r12,-16(%rbp)
	movl	$0,%ebx
	movq	$nums,%r12
	movl	$0,%edx
	L1:
		cmpl	$4,%ebx
		je L2
		movl	(%r12),%eax
		movl	%eax,%edx
		and	$0x0001,%edx
		cmpl	$0x0000,%edx
		je L3
		addl	$1,%ebx
		addq	$4,%r12
		jmp L1
	L2:
		movq	$0,%rax
		movq	-8(%rbp),%rbx
		movq	-16(%rbp),%r12
		leave
		ret
	L3:
		movq	$Sf,%rdi
		movl	%eax,%esi
		call	printf
		addl	$1,%ebx
		addq	$4,%r12
		jmp L1
	
