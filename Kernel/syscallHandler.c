#include <stdint.h>
#include <defs.h>
#include <string.h>
#include <keyboard.h>
#include <naiveRTC.h>
#include <naiveGraphicsConsole.h>

//extern uint64_t info;

static void sys_write_handler(unsigned int fd, const char * buffer, int bytes){
    if (fd == STDOUT){
        ngc_print(buffer); //deberia recibir los bytes
    }
}


static void sys_read_handler(unsigned int fd,  char * buffer, int bytes){
    if (fd == STDIN || fd == KBDIN){
        uint64_t aux = 0;
        int flag = 0;
		while(!flag && *buffer != '\t' ){
            _hlt();
            if (getLastChar() == '\n'){
                flag = 1;
            }
        }
        uint64_t n = getBufferLength();
        memcpy(buffer,getBuffer(),n);
    }
}

static uint64_t sys_time_handler(){
    return (_NRTCGetHours()) | ((uint64_t)_NRTCGetMins() << 8) | ((uint64_t)_NRTCGetSeconds() << 16);
}

static void sys_clear_screen_handler(Color color) {
    ngc_paint_screen(color);
}

static uint64_t sys_screenshot_handler(){
    //return info;
}

// 2 por altura y ancho
static uint64_t * sys_screenData_handler(){
    uint64_t data[2] = {{0};}
    data[0] = getWidth();
    data[1] = getHeight();
    return data;
}

static void (* syscalls[30])(void * rsi, void * rdx, void * rcx, void * r8, void * rax) = {sys_read_handler, sys_write_handler, sys_time_handler, sys_clear_screen_handler, sys_screenshot_handler, sys_screenData_handler};

//  paso syscall_id por rax, se come r10 por rcx, y r9 por eax
void syscallDispatcher(void * rdi, void * rsi, void * rdx, void * rcx, void * r8, uint64_t rax){
    syscalls[rax](rdi, rsi, rdx, rcx, r8);
}

