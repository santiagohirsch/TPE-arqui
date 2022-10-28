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

static void sys_clear_screen_handler() {
    Color black = {0, 0, 0};
    Color gray = {0x7f,0x7f,0x7f};
    Color white = {0xFF, 0xFF, 0xFF};
    Color red = {0, 0, 0xFF};

    ngc_paint_screen(black);
    ngc_print_pixels(150, 200, 80, 50, white);
    ngc_print_pixels(200, 200, 80, 50, red);
    ngc_print_pixels(250, 200, 80, 50, white);
}

static uint64_t sys_screenshot_handler(){
    //return info;
}

static void (* syscalls[30])(void * rsi, void * rdx, void * rcx, void * r8, void * rax) = {sys_read_handler, sys_write_handler, sys_time_handler, sys_clear_screen_handler, sys_screenshot_handler};

//  paso syscall_id por rax, se come r10 por rcx, y r9 por eax
void syscallDispatcher(void * rdi, void * rsi, void * rdx, void * rcx, void * r8, uint64_t rax){
    syscalls[rax](rdi, rsi, rdx, rcx, r8);
}

