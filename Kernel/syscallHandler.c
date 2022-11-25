#include <stdint.h>
#include <defs.h>
#include <string.h>
#include <keyboard.h>
#include <naiveRTC.h>
#include <naiveGraphicsConsole.h>
#include <time.h>
#include <speaker.h>
#include <interrupts.h>

extern uint64_t info[17];
extern uint8_t screenshot;

typedef int64_t (*syscallT) (uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

static void sys_write_handler(uint64_t fd, uint64_t buffer, uint64_t bytes){
    if (fd == STDOUT) {
        for (uint64_t i = 0; i < bytes; i++){
            ngc_printChar(((char*)buffer)[i]);
        }
    }
}

static int64_t sys_read_handler(uint64_t fd, char * buffer, uint64_t bytes){
    if (fd != STDIN && fd != KBDIN) return -1;
    int64_t i = 0;
    char c;
    while(i < bytes && (c = getFirstChar()) != 0xFF) {
        buffer[i] = c;
        i++;
    }
    return i;
}

static uint64_t sys_time_handler(){
    return (_NRTCGetHours()) | ((uint64_t)_NRTCGetMins() << 8) | ((uint64_t)_NRTCGetSeconds() << 16);
}

static uint8_t sys_inforeg_handler(uint64_t regVec[17]){
    if (screenshot){
        for (int i = 0; i < 17; i++)
        {
            regVec[i] = info[i];
        }
        
    }
    return screenshot;
}

static void sys_font_handler(uint64_t level){
    changeFontSize(level);
}

static void sys_printColor_handler(const char *buffer, uint64_t color){
    ngc_printColor(buffer, color);
}

static void sys_clear_screen_handler(uint64_t color) {
    ngc_paint_screen(color);
}

// 2 por altura y ancho
static void sys_screenData_handler(uint16_t * data){
    data[0] = ngc_getWidth();
    data[1] = ngc_getHeight();
    return;
}

static void sys_paint_rect_handler(uint64_t fromX, uint64_t fromY, uint16_t width, uint16_t height, uint64_t color) {
    ngc_print_pixels(fromX, fromY, width, height, color);
}

static uint64_t sys_ticks_handler(){
    return ticks_elapsed();
}

static void sys_beeper_handler(uint64_t frequency, uint64_t interval) {
    beep(frequency);
    wait(interval);
    stopBeep();
}

static syscallT syscalls[]  = {
    (syscallT) sys_read_handler, 
    (syscallT) sys_write_handler, 
    (syscallT) sys_time_handler, 
    (syscallT) sys_inforeg_handler, 
    (syscallT) sys_font_handler, 
    (syscallT) sys_printColor_handler, 
    (syscallT) sys_clear_screen_handler, 
    (syscallT) sys_screenData_handler, 
    (syscallT) sys_paint_rect_handler, 
    (syscallT) sys_ticks_handler, 
    (syscallT) sys_beeper_handler
};

//  paso syscall_id por rax, se come r10 por rcx, y r9 por rax
int64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t rax){
    return syscalls[rax](rdi, rsi, rdx, rcx, r8);
}

