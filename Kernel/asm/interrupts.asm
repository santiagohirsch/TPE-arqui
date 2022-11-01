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
EXTERN keyboard_handler

GLOBAL info
GLOBAL screenshot


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

	mov [regdata + (1*8)], rax
	mov rax, $;[rsp] ;rip = int return address
	mov [regdata], rax 
	mov [regdata + (2*8)], rbx
	mov [regdata + (3*8)], rcx
	mov [regdata + (4*8)], rdx
	mov [regdata + (5*8)], rsi
	mov [regdata + (6*8)], rdi
	mov [regdata + (7*8)], rbp
	mov rax, rsp ; We get the value of RSP 
	add rax, 0x28 ; We add bytes in order to compensate for the values pushed since the exception occurred and called the exception handler
	mov [regdata + (8*8)], rax;rsp
	mov [regdata + (9*8)], r8
	mov [regdata + (10*8)], r9
	mov [regdata + (11*8)], r10
	mov [regdata + (12*8)], r11
	mov [regdata + (13*8)], r12
	mov [regdata + (14*8)], r13
	mov [regdata + (15*8)], r14
	mov [regdata + (16*8)], r15
	mov rax, [rsp+8] ; We get the value of RFLAGS (it is pushed when an interrupt occurs).
	mov [regdata + (17*8)], rax

	
	
	

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
_irq01Handler:
	;irqHandlerMaster 1
	pushState
 	mov rax, 0
    in al, 0x60
	cmp al, 0x1D ;me fijo si la tecla es un ctrl
	jne .continue
	;Guardo: rip, rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8, r9, r10, r11, r12, r13, r14, r15 
	mov [info+(1*8)], rax
	mov rax, $
	mov [info], rax ;rip
	mov [info+(2*8)], rbx
	mov [info+(3*8)], rcx
	mov [info+(4*8)], rdx
	mov [info+(5*8)], rsi
	mov [info+(6*8)], rdi
	mov [info+(7*8)], rbp
	mov [info+(8*8)], rsp
	mov [info+(9*8)], r8
	mov [info+(10*8)], r9
	mov [info+(11*8)], r10
	mov [info+(12*8)], r11
	mov [info+(13*8)], r12
	mov [info+(14*8)], r13
	mov [info+(15*8)], r14
	mov [info+(16*8)], r15
	mov byte[screenshot], 1
	jmp .end
.continue:
	cmp al, 0x9D	;me fijo si la tecla es un ctrl 
	je .end

	mov rdi, rax
	call keyboard_handler
.end:
	mov al, 20h
	out 20h, al
	popState
	iretq
	

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
	info resq 17
	regdata resq 18
	screenshot resb 1 ;reservo un bit para poner en 1 si hubo un screenshot
