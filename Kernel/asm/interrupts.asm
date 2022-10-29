GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt
GLOBAL _cli
GLOBAL _sti

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _irq10Handler
GLOBAL _irq80Handler


GLOBAL _invalidOpCodeInterruption
GLOBAL _divisionByZeroInterruption

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallDispatcher


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
	;pushState
	
	;me guardo los registros para imprimir
	;Guardo: rip, rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8, r9, r10, r11, r12, r13, r14, r15, rflags
	mov [regdata], rax
	mov [regdata+8], rbx
	mov [regdata+16], rcx
	mov [regdata+24], rdx
	mov [regdata+32], rsi
	mov [regdata+40], rdi
	mov [regdata+48], rbp
	mov [regdata+64], r8
	mov [regdata+72], r9
	mov [regdata+80], r10
	mov [regdata+88], r11
	mov [regdata+96], r12
	mov [regdata+104], r13
	mov [regdata+112], r14
	mov [regdata+120], r15

	
	;marengo stealed shit
	mov rax, rsp ; We get the value of RSP when the exception ocurred by adding the amount of pushed bytes to the current value of RSP.
	add rax, 0x28
	mov [regdata+(8*8)], rax
	mov rax, [rsp] ; We get the value of RIP when the exception ocurred by taking the interruption's return address.
	mov [regdata+128], rax
	mov rax, [rsp+8] ; We get the value of RFLAGS the same way (it is pushed when an interrupt occurs).
	mov [regdata+136], rax

	mov rdi, %1 ; pasaje de parametro
	mov rsi, regdata
	call exceptionDispatcher

	;popState
	;iretq
%endmacro


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
    out		0A1h, al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler: irqHandlerMaster 0

;Keyboard
_irq01Handler: irqHandlerMaster 1

;Cascade pic never called
_irq02Handler: irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler: irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler: irqHandlerMaster 4

;USB
_irq05Handler: irqHandlerMaster 5


;Syscall
_irq80Handler:
	;Syscall params: rdi rsi rdx r10 r8	r9
	;C params: rdi rsi rdx rcx r8 r9
	push rbp
	mov rbp, rsp
	mov rcx, r10
	mov r9, rax
	call syscallDispatcher
	
	mov rsp, rbp
	pop rbp
	iretq

;Zero Division Exception
_divisionByZeroInterruption:
	exceptionHandler 00h

;Invalid Op Code Exception
_invalidOpCodeInterruption:
	exceptionHandler 06h


haltcpu:
	cli
	hlt
	ret

SECTION .bss
	aux resq 1
	regdata resq 18
