GLOBAL sys_int_80
GLOBAL _hlt
GLOBAL getRegister
global getRDI
global divideZero
global opCodeEx
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
;Special case for rdi because its the first register that recieves a parameter
getRDI:
    push rbp
    mov rbp, rsp
    mov rax, rdi
    mov rsp, rbp
    pop rbp
    ret

;void getRegister(int * regs);
getRegister:
; saving the registers on a vector direction we get on rdi
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
    mov rax, $
    mov [rdi + 60], rax
ret


divideZero:
    mov rax,0
    mov rbx,9
    div rbx
    ret

opCodeEx:
    push rbp
    mov rbp, rsp
    UD2
    mov rsp, rbp
    pop rbp
    ret

