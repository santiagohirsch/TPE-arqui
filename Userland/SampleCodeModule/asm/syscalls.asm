GLOBAL sys_write
GLOBAL sys_read
GLOBAL sys_time
GLOBAL sys_inforeg
GLOBAL sys_changeFontSize
GLOBAL sys_printColor

section .text
sys_read:
    mov rax, 0x00
    int 80h
    ret
sys_write:
    mov rax, 0x01
    int 80h
    ret
sys_time:
    mov rax, 0x02
    int 80h
    ret
sys_inforeg:
    mov rax, 0x03
    int 80h
    ret
sys_changeFontSize:
    mov rax, 0x04
    int 80h
    ret
sys_printColor:
    mov rax, 0x05
    int 80h
    ret