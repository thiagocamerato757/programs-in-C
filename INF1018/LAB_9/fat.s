.text
.globl fat
fat:
    pushq %rbp        
    movq %rsp, %rbp    
    subq $16, %rsp     
    movl %edi, -4(%rbp)
    cmpl $0, %edi      
    je L1           

    decl %edi          
    call fat            

    movl -4(%rbp), %edi  
    imull %edi, %eax 
    jmp L2  

L1:
    movl $1, %eax    
L2:
   leave 
   ret

