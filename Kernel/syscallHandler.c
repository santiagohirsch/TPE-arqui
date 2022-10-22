#include <stdint.h>
#include <defs.h>

static void sys_write_handler(unsigned int fd, const char * buffer, int bytes){
    if (fd == STDOUT){
        ngc_print(buffer); //deberia recibir los bytes
    }
}


static void (* syscalls[30])(void * rdi,void * rsi,void * rdx,void * r10,void * r8,void * r9) = {sys_write_handler};
 

void syscallDispatcher(uint64_t rax, void * rdi, void * rsi, void * rdx, void * r10, void * r8, void * r9){
    syscalls[rax](rdi, rsi, rdx, r10, r8, r9);
}

