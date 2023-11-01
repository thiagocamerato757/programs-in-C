.text
.globl foo
	foo:
	pushq %rbp
	movq  %rsp,%rbp
	incl  %edi
        movq  %rdi,%rax
	leave 
	ret
