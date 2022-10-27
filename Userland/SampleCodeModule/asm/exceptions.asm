GLOBAL exc_invalidOpCode
GLOBAL exc_divideByZero

section .text
exc_invalidOpCode:
    mov cr6, rax
    ret

exc_divideByZero:
    mov rax, 0
    div rax
	ret
