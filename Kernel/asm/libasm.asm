GLOBAL cpuVendor
GLOBAL getSeconds
GLOBAL getMinutes
GLOBAL getHours
GLOBAL getKey
GLOBAL sys_write
GLOBAL outb
GLOBAL inb
GLOBAL hlt
GLOBAL getRDI
GLOBAL getRegisters
GLOBAL getMemory
GLOBAL enterCriticalRegion




extern sysInterruptions
section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret


getSeconds:
	push rbp
	mov  rbp,rsp
	mov al, 0
	out 70h, al
	in al, 71h
	mov rsp,rbp
	pop rbp
	ret

getMinutes:
	push rbp
	mov  rbp,rsp
	mov al, 2
	out 70h, al
	in al, 71h
	mov rsp,rbp
	pop rbp
	ret


getHours:
	push rbp
	mov  rbp,rsp
	mov rax,0
	mov al, 4
	out 70h, al
	in al, 71h
	mov rsp,rbp
	pop rbp
	ret

getKey:
	push rbp
	mov rbp,rsp
	mov rax,0
	in al,60h
	mov rsp,rbp
	pop rbp
	ret


sys_write:
	push rbp
	mov rbp, rsp
	mov rax, 1
	int 80h
	mov rsp,rbp
	pop rbp
	ret

inb:
	push rbp
	mov rbp, rsp
	mov rdx, rdi
	mov rax, 0
    in al, dx
	mov rsp, rbp
	pop rbp
	ret

outb:
	push rbp
	mov rbp, rsp
	mov rax, rsi
	mov rdx, rdi
	out dx, al
	mov rsp, rbp
	pop rbp
	ret

hlt:
	sti
	hlt
	ret

enterCriticalRegion:
	push rbp
	mov rbp, rsp

	mov eax, 1
	xchg eax, [rdi]

	mov rsp, rbp
	pop rbp

	ret

;void getMemory(int memoryPos, unsigned char * res)
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
