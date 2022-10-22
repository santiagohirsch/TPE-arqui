GLOBAL sys_write
GLOBAL sys_read

section .text
sys_read:
    mov rax, 0x00
    int 80h
    ret
sys_write:
    mov rax, 0x01
    int 80h
    ret
