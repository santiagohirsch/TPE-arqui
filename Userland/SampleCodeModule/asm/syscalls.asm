GLOBAL sys_write
GLOBAL sys_read
GLOBAL sys_time
GLOBAL sys_inforeg
GLOBAL sys_changeFontSize
GLOBAL sys_printColor
GLOBAL sys_clear_screen
GLOBAL sys_getScreenData
GLOBAL sys_paint_rect
GLOBAL sys_getTicks
GLOBAL sys_timed_read
GLOBAL sys_beeper

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

sys_clear_screen:
    mov rax, 0x06
    int 80h
    ret

sys_getScreenData:
    mov rax, 0x07
    int 80h
    ret

sys_paint_rect:
    mov rax, 0x08 
    mov r10, rcx
    int 80h
    ret

sys_getTicks:
    mov rax, 0x09
    int 80h
    ret


sys_beeper:
    mov rax, 0x0A
    int 80h
    ret
