GLOBAL excInvalidOpCode
GLOBAL excDivideByZero

section .text
excInvalidOpCode:
; veremos 

excDivideByZero:
    mov rax,0
    div rax
	ret

section .bss