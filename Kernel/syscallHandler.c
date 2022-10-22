#include <stdint.h>
#include <defs.h>
/*
static void sys_write_handler(unsigned int fd, const char * buffer, int bytes){
    if (fd == STDOUT){
        ngc_print(buffer); //deberia recibir los bytes
    }
}


static void sys_read_handler(unsigned int fd, const char * buffer, int bytes){
    return;
}

static void (* syscalls[30])(void * rsi, void * rdx, void * rcx void * r8) = {sys_read_handler, sys_write_handler};
 */
//  paso syscall_id por rax, se come r10 por rcx, y r9 por eax
void syscallDispatcher(void * rdi, void * rsi, void * rdx, void * rcx, void * r8, void * rax){
    //syscalls[rax](rdi, rsi, rdx, rcx, r8);
    ngc_print("hola"); //deberia recibir los bytes
}

