GLOBAL sys_int_80

sys_int_80:
    push rbp
    mov rbp, rsp
    int 0x80
    mov rsp, rbp
    pop rbp
    ret
