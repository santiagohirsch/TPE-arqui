GLOBAL _NRTCGetHours
GLOBAL _NRTCGetMins
GLOBAL _NRTCGetSeconds

section .text

_NRTCGetHours:

    mov rax, 0x04
    call _RTC

    ret

_NRTCGetMins:

    mov rax, 0x02
    call _RTC
    
    ret

_NRTCGetSeconds:
    
    mov rax, 0x00
    call _RTC

    ret

_RTC:
    out 70h, al
    in al, 71h
    ret
