GLOBAL sys_int_80
GLOBAL _hlt
GLOBAL _sti

sys_int_80:
    push rbp
    mov rbp, rsp
    int 0x80
    mov rsp, rbp
    pop rbp
    ret

_hlt:
	;sti
	hlt
	ret

_sti:
    sti
    ret
