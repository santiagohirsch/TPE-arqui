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

static void sys_write_handler(uint64_t fd, uint64_t buffer, uint64_t bytes){
    if (fd == STDOUT) {
        for (uint64_t i = 0; i < bytes; i++){
            ngc_printChar(((char*)buffer)[i]);
        }
    }
}

static void sys_read_handler(uint64_t fd, uint64_t buffer, uint64_t bytes){
    if (fd != STDIN && fd != KBDIN) return;
    _hlt();
    ((char*)buffer)[0] = getFirstChar();
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

static void (* syscalls[]) (uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t rax) = {sys_read_handler, sys_write_handler, sys_time_handler, sys_inforeg_handler, sys_font_handler, sys_printColor_handler, sys_clear_screen_handler, sys_screenData_handler, sys_paint_rect_handler, sys_ticks_handler, sys_beeper_handler};

//  paso syscall_id por rax, se come r10 por rcx, y r9 por rax
void syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t rax){
    syscalls[rax](rdi, rsi, rdx, rcx, r8);
}

