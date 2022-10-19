GLOBAL _getFD

section .text

_getFD:
    push rbp
    mov rbp, rsp
    mov rax, rdi
    mov rsp, rbp
    pop rbp
    ret