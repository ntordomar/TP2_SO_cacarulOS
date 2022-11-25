global loader
global clearStackAndMain
extern main
extern getStackBase
extern initializeKernelBinary

loader:
	call initializeKernelBinary	; Set up the kernel binary, and get thet stack address
	mov rsp, rax				; Set up the stack with the returned address
	call main
hang:
	cli
	hlt	; halt machine should kernel return
	jmp hang

clearStackAndMain:
	call getStackBase
	mov rsp, rax
	ret
