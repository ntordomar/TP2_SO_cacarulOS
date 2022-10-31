GLOBAL sys_int_80
GLOBAL _hlt
GLOBAL getRegisters
global getRDI
global getMemory
global divideZero
global opCode
sys_int_80:
    push rbp
    mov rbp, rsp
    int 0x80
    mov rsp, rbp
    pop rbp
    ret

_hlt:
    sti
    hlt
    ret

;int getRax();
getRax:
    nop
    ret

;int getRDI();
getRDI:
    push rbp
    mov rbp, rsp
    mov rax, rdi
    mov rsp, rbp
    pop rbp
    ret

;void getRegister(int * regs);
getRegisters:
; no realizamos el armado del stackframe pues necesitamos los registros del rbp y rsp
    mov [rdi], rax
    mov [rdi + 4],rbx
    mov [rdi + 8], rcx
    mov [rdi + 12], rdx
    mov [rdi + 16], rsi
    mov [rdi + 20], rbp
    mov [rdi + 24], rsp
    mov [rdi + 28], r8
    mov [rdi + 32], r9
    mov [rdi + 36], r10
    mov [rdi + 40], r11
    mov [rdi + 44], r12
    mov [rdi + 48], r13
    mov [rdi + 52], r14
    mov [rdi + 56], r15
ret

;void getMemory(int memoryPos, int * res)
;RDI la memoryPos RSI res
getMemory:
    push rbp
    mov rbp, rsp
    mov R8, 0
    mov rax,0
    loop:
    mov  al, [RDI] 
    mov  [RSI], al
    inc RDI
    inc RSI
    inc R8
    cmp R8, 32
    je exit
    jmp loop

exit:
    mov rsp, rbp
    pop rbp
    ret

divideZero:
    mov rax,0
    mov rbx,9
    div rbx
    ret

opCode:
    ;
    ;