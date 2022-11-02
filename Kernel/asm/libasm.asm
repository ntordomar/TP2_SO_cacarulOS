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

;int getRDI();
getRDI:
    push rbp
    mov rbp, rsp
    mov rax, rdi
    mov rsp, rbp
    pop rbp
    ret

;void getRegister(uint_64 * regs);
getRegisters:
; saving the registers on a vector direction we get on rdi
    mov [rdi], rax
	mov rax, $
	mov [rdi + 120], rax
    mov [rdi + 8],rbx
    mov [rdi + 16], rcx
    mov [rdi + 24], rdx
    mov [rdi + 32], rsi
    mov [rdi + 40], rbp
    mov [rdi + 48], rsp
    mov [rdi + 56], r8
    mov [rdi + 64], r9
    mov [rdi + 72], r10
    mov [rdi + 80], r11
    mov [rdi + 88], r12
    mov [rdi + 96], r13
    mov [rdi + 104], r14
    mov [rdi + 112], r15
ret



