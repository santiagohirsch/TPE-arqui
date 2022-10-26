GLOBAL sys_write
GLOBAL sys_read
GLOBAL sys_time
GLOBAL sys_screenshot
GLOBAL sys_clear_screen

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
sys_clear_screen:
    mov rax, 0x03
    int 80h
    ret

;sys_screenshot:
;    mov rax, 0x04
;    int 80h
;    ret