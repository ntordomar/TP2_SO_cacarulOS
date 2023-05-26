
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt
GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL int80Handler
GLOBAL _exception6Handler
GLOBAL restore_stack
GLOBAL createStack
GLOBAL save_original_regs

;----------------------
;inforeg and exceptions arrays of registers.
GLOBAL registers
GLOBAL capturedReg
GLOBAL excepRegs
;----------------------

GLOBAL _exception0Handler
EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sys_call_handler
EXTERN keyHandler
EXTERN getStackBase
EXTERN switchProcess
EXTERN schedulerIsEnabled
EXTERN getRegistersDebugger


SECTION .text



%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro pushStateNoRax 0
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState
	mov rdi, %1 ; irqDispatcher parameter.
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	mov byte [capturedReg], 0

	; saving an array of registers: RAX, RBX, RCX, RDX, RSI, RDI, RBP, RSP, R8, R9, R10, R11, R12, R13
	; R14, R15, RIP
	mov [excepRegs], rax
    mov [excepRegs + 8], rbx
    mov [excepRegs + 16], rcx
    mov [excepRegs + 24], rdx
    mov [excepRegs + 32], rsi
	mov [excepRegs + 40], rdi
    mov [excepRegs + 48], rbp
    mov [excepRegs + 64], r8
    mov [excepRegs + 72], r9
    mov [excepRegs + 80], r10
    mov [excepRegs + 88], r11
    mov [excepRegs + 96], r12
    mov [excepRegs + 104], r13
    mov [excepRegs + 112], r14
    mov [excepRegs + 120], r15

	mov rax, rsp
	
	mov [excepRegs+ 56], rax  ;RSP

	mov rax, [rsp]
	mov [excepRegs + 128], rax ;RIP
	

	
	mov rdi, %1 ; irqDispatcher parameter.
	call exceptionDispatcher
	
	;Restoring original registers
	mov rax, [ogRegs+8*0]
	mov rbx, [ogRegs+8*1]
	mov rcx, [ogRegs+8*2]
	mov rdx, [ogRegs+8*3]
	mov rsi, [ogRegs+8*4]
	mov rdi, [ogRegs+8*5]
	mov rbp, [ogRegs+8*6]
	mov r8,  [ogRegs+8*7]
	mov r9,  [ogRegs+8*8]
	mov r10, [ogRegs+8*9]
	mov r11, [ogRegs+8*10]
	mov r12, [ogRegs+8*11]
	mov r13, [ogRegs+8*12]
	mov r14, [ogRegs+8*13]
	mov r15, [ogRegs+8*14]
	
	mov rax, [ogRegs+8*16]	;RIP
	mov [rsp], rax
	

	iretq
%endmacro

	

int80Handler:
	pushState
	call sys_call_handler
	popState
	iretq	

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mask of 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	cli
	pushState ; Preservo el estado del proceso que esta corriendo

	
	call schedulerIsEnabled
	cmp rax,0
	je .noSwitch

	mov rdi, rsp ; Paso como argumento el stack pointer actual para poder intercambiar el proceso
	mov rsi, ss
	call switchProcess
	mov rsp,rax ; Recibo el nuevo stack pointer y se lo asigno a rsp para empezar a correr el nuevo proceso.

	.noSwitch:
	mov rdi, 0 ; irqDispatcher parameter.
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al
	popState
	sti
	iretq


;Keyboard
_irq01Handler:
	pushState
	mov rax, 0
	in al, 0x60
	cmp al, 0x1D ; ctrl key
	jne noCtrl
	
	; saving an array of registers: RAX, RBX, RCX, RDX, RSI, RDI, RBP, RSP, R8, R9, R10, R11, R12, R13
	; R14, R15, RIP
    mov [registers + 8], rbx
    mov [registers + 16], rcx
    mov [registers + 24], rdx
    mov [registers + 32], rsi
	mov [registers + 40], rdi
    mov [registers + 48], rbp
    mov [registers + 64], r8
    mov [registers + 72], r9
    mov [registers + 80], r10
    mov [registers + 88], r11
    mov [registers + 96], r12
    mov [registers + 104], r13
    mov [registers + 112], r14
    mov [registers + 120], r15

	mov rax, rsp
	add rax, 160			  ;fixing stack height so that rax value is RSP value.
	mov [registers+ 56], rax  ;RSP

	mov rax, [rsp+15*8]
	mov [registers + 128], rax ;RIP

	mov rax, [rsp + 14*8]	;RAX
	mov [registers], rax

	mov byte [capturedReg], 1
	jmp exit

noCtrl:
	cmp al, 0x9D	; checking if the key is a ctrl release
	je exit
	mov rdi, rax
	call keyHandler
	jmp exit
	
exit:
	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al
	popState
	iretq
	
	

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Op Code Exception
_exception6Handler:
	exceptionHandler 6

haltcpu:
	cli
	hlt
	ret

save_original_regs:
	; Saving registers: RAX, RBX, RCX, RDX, RSI, RDI, RBP, RSP, R8, R9, R10, R11, R12, R13
	; R14, R15, RIP
    mov [ogRegs+8*0], 	rax
	mov [ogRegs+8*1], 	rbx
	mov [ogRegs+8*2], 	rcx
	mov [ogRegs+8*3], 	rdx
	mov [ogRegs+8*4], 	rsi
	mov [ogRegs+8*5], 	rdi
	mov [ogRegs+8*6], 	rbp
	mov [ogRegs+8*7], 	r8
	mov [ogRegs+8*8], 	r9
	mov [ogRegs+8*9], 	r10
	mov [ogRegs+8*10], 	r11
	mov [ogRegs+8*11], 	r12
	mov [ogRegs+8*12], 	r13
	mov [ogRegs+8*13], 	r14
	mov [ogRegs+8*14], 	r15
	mov [ogRegs+8*15], rsp	;RSP
	mov rax, [rsp]   ; RSP contains the return adress, so we get the RIP
	mov [ogRegs+8*16], rax
	ret

restore_stack:
	mov [prevBS],rbx
	pop rbx
	call getStackBase
	mov rsp,rax
	push rbx
	mov rbx,[prevBS]
	ret

createStack: ;RDI EL STACK - RSI CODE - RDX ARGS
	mov r8,rsp ; preservo viejo RSP
	mov rsp,rdi
	push 0x0 ; el SS
	push rdi ; el RSP
	push 0x202 ; el RFLAGS
	push 0x8 ; el CS
	push rsi ; el RIP
	push 0x0 ; el RAX
	mov rdi,rdx ; los argumentos
	push 0x1 ;rbx
    push 0x2
    push 0x3
    push 0x4
    push rdx ; no tocar, son los argumentos
    push 0x6
    push 0x7
    push 0x8
    push 0x9
    push 0x10
    push 0x11
    push 0x12
    push 0x13
    push 0x14
	mov rax,rsp ; el RSP
	mov rsp,r8 ; restauro el RSP
	ret




SECTION .data
	capturedReg dq 0	;regs captured -> 1. regs not captured yet -> 0

SECTION .bss
	registers resq 17	;registrs when taking SCREENSHOT
	excepRegs resq 17	;registrs when there is an exception
	prevBS 	resq 1
	ogRegs resq 17		;Vector for original registers
	