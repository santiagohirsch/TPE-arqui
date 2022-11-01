GLOBAL _beep_start
GLOBAL _beep_stop

_beep_start:
  push rbp
  mov rbp, rsp

  mov al, 0xB6
  out 43h,al

  mov rbx, rdi
  mov rax, 0
  mov ax, bx

  out 42h,al
  mov al,ah
  out 42h,al

  in al, 61h 
  or al, 03h 
  out 61h,al

  mov rsp, rbp
  pop rbp
  ret

_beep_stop:
	push rbp
  mov rbp, rsp

  in al, 61h
  and al, 0xFC
  out 61h, al

	mov rsp, rbp
  pop rbp
  ret