GLOBAL cpuVendor
GLOBAL sys_write
section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

sys_write:
	push rbp
    mov rbp, rsp   
    mov rax, 1
	int 80h
	mov rsp, rbp
	pop rbp
    ret