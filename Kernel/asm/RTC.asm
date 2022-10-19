GLOBAL _NRTCGetHours
GLOBAL _NRTCGetMins
GLOBAL _NRTCGetSeconds
section .text
_NRTCGetHours:
mov rax, 4
call _RTC
ret

_NRTCGetMins:
mov rax, 2
call _RTC
ret

_NRTCGetSeconds:
mov rax, 0
call _RTC
ret

_RTC:
out 70h, al
in al, 71h
ret