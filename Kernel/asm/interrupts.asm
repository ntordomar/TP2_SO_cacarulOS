
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

;----------------------
;variables para inforeg y exceptions
GLOBAL registers
GLOBAL capturedReg
GLOBAL excepRegs
;----------------------

GLOBAL _exception0Handler
EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sys_call_handler
EXTERN keyHandler


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

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	pushState
	; guardo el vector de registros: RAX, RBX, RCX, RDX, RSI, RDI, RBP, RSP, R8, R9, R10, R11, R12, R13
	; R14, R15, RIP
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
	add rax, 160			  ;corregimos la altura del stack
	mov [excepRegs+ 56], rax  ;RSP

	mov rax, [rsp+15*8]
	mov [excepRegs + 128], rax ;RIP

	mov rax, [rsp + 14*8]	;obtengo RAX
	mov [excepRegs], rax

	
	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState
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
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	pushState
	mov rax, 0
	in al, 0x60
	cmp al, 0x1D ; es la tecla ctrl
	jne noCtrl
	
	; guardo el vector de registros: RAX, RBX, RCX, RDX, RSI, RDI, RBP, RSP, R8, R9, R10, R11, R12, R13
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
	add rax, 160			  ;corregimos la altura del stack
	mov [registers+ 56], rax  ;RSP

	mov rax, [rsp+15*8]
	mov [registers + 128], rax ;RIP

	mov rax, [rsp + 14*8]	;obtengo RAX
	mov [registers], rax

	mov byte [capturedReg], 1
	jmp exit

noCtrl:
	cmp al, 0x9D	;me fijo si la tecla es un ctrl release
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

_exception6Handler:
	exceptionHandler 6

haltcpu:
	cli
	hlt
	ret


SECTION .bss
	aux resq 1
	registers resq 17	;registros al hacer una captura
	excepRegs resq 17	;registros al haber una excepcion
	capturedReg resb 1	;indica si se realizo una captura(=1) o no(=0)
	