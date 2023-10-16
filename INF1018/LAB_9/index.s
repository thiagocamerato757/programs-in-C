.text
.globl foo
foo:
    pushq %rbp              
    movq %rsp, %rbp
    subq $16,%rsp      
    movl $0,%r10d # i = 0
    movl $0,%r11d # s = 0
    movq %rdi,%rdx # a = %rdx
    
   
    
l1:
    cmpl %esi,%r10d   # i < n
    jge l3        
    movl %r10d,%ecx  # %ecx = i
    imull $4,%ecx # %ecx *= 4
    addq %rcx,%rdx # %rdx = %rdx + %rcx
    addl (%rdx),%r11d # s += a[i]
    cmpl $0,(%rdx)   # a[i] == 0
    je l2   
    incl %r10d # i++
    jmp l1
l2:
    movl %r11d, (%rdx) # a[i] = s
    movl $0,%r11d # s =0
    incl %r10d   # i++
    jmp l1          
l3:
    leave        
    ret       

       
