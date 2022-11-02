GLOBAL exc_invalidOpCode
GLOBAL exc_divisionByZero

section .text
exc_invalidOpCode:
    mov cr6, rax    ; -> InvalidOpCode Exception
    ret

exc_divisionByZero:
    mov rax, 0
    div rax     ; -> DivideByZero Exception
    ret
