GLOBAL loader
GLOBAL restart
extern main
extern initializeKernelBinary
extern getStackBase

section .text

loader:
	call initializeKernelBinary	; Set up the kernel binary, and get thet stack address
	jmp rt

restart:
	call getStackBase
rt:	mov rsp, rax				; Set up the stack with the returned address
	call main
hang:
	cli
	hlt	; halt machine should kernel return
	jmp hang
