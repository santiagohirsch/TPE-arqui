GLOBAL _NRTCGetHours
GLOBAL _NRTCGetMins
GLOBAL _NRTCGetSeconds

section .text

_NRTCGetHours:
    push rbp
    mov rbp, rsp

    mov rax, 0x04
    call _RTC

    mov rsp, rbp
    pop rbp
    ret

_NRTCGetMins:
    push rbp
    mov rbp, rsp

    mov rax, 0x02
    call _RTC
    
    mov rsp, rbp
    pop rbp
    ret

_NRTCGetSeconds:
    push rbp
    mov rbp, rsp
    
    mov rax, 0x00
    call _RTC

    mov rsp, rbp
    pop rbp
    ret

_RTC:
    out 70h, al
    in al, 71h
    ret
