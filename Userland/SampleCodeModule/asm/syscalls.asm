GLOBAL sys_write
GLOBAL sys_read

section .text
sys_read:
    mov rax, 0
    int 80h
sys_write:
    mov rax, 1
    int 80h
